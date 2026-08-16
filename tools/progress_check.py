#!/usr/bin/env python3
"""Independent progress measurement, taken from the linked ELF rather than the map.

`tools/progress.py` parses the textual linker map.  This reads the ELF symbol
table and the input objects instead, so the two are wrong in different ways and
can be used to check each other:

  * the map omits file-local symbols; the symbol table has them
  * the map's per-function length is a difference between consecutive symbols,
    so trailing data inside a code section is charged to the last function;
    here a function's length is its st_size

Both tools have to agree about what a function *is*.  splat types several kinds
of non-function as @function -- interior branch labels (`.L1500ABCD`,
`L80001234`), padding markers (`func_XXXX_pad`) and rodata symbols (`D_*`) --
and none of those carries a `#pragma GLOBAL_ASM`, so counting them scores each
one as decompiled C and inflates both halves of the fraction.

A function is DECOMPILED here only if an object built from a C translation unit
defines it and no translation unit still carries a GLOBAL_ASM stub for it.
Functions supplied by handwritten .s objects are reported separately: they are
not decompiled and never will be.

    python3 tools/progress_check.py [repo root]
"""
import bisect
import os
import re
import struct
import sys

SECTIONS = (".init", ".game", ".debugger")
STT_FUNC = 2
SHN_UNDEF, SHN_COMMON = 0, 0xFFF1

NOT_A_FUNCTION = re.compile(r"^(\.L|L[0-9A-Fa-f]{6,}|D_)|_pad$")


def is_function(name):
    return not NOT_A_FUNCTION.search(name)


def read_elf(path):
    """Return (blob, section headers, name lookup) for a big-endian ELF32."""
    with open(path, "rb") as fh:
        blob = fh.read()
    if blob[:4] != b"\x7fELF" or blob[4] != 1 or blob[5] != 2:
        return None
    e_shoff, = struct.unpack_from(">I", blob, 0x20)
    e_shentsize, e_shnum, e_shstrndx = struct.unpack_from(">HHH", blob, 0x2E)
    fields = "name type flags addr off size link info align entsize".split()
    shs = [dict(zip(fields, struct.unpack_from(">10I", blob,
                                               e_shoff + i * e_shentsize)))
           for i in range(e_shnum)]

    def name_at(off):
        return blob[off:blob.index(b"\0", off)].decode(errors="replace")

    shstr = shs[e_shstrndx]
    for sh in shs:
        sh["sname"] = name_at(shstr["off"] + sh["name"])
    return blob, shs, name_at


def symbols(path):
    """Yield (name, value, size, type, section index) for every symbol."""
    parsed = read_elf(path)
    if not parsed:
        return
    blob, shs, name_at = parsed
    symtab = next((s for s in shs if s["sname"] == ".symtab"), None)
    if not symtab or not symtab["entsize"]:
        return
    strtab = shs[symtab["link"]]
    for i in range(symtab["size"] // symtab["entsize"]):
        off = symtab["off"] + i * symtab["entsize"]
        st_name, st_value, st_size, st_info, _other, st_shndx = \
            struct.unpack_from(">IIIBBH", blob, off)
        yield (name_at(strtab["off"] + st_name), st_value, st_size,
               st_info & 0xF, st_shndx)


def collect_functions(elf_path):
    """Every real function in the three code sections, sized and located."""
    blob, shs, _ = read_elf(elf_path)
    section_of = {i: s["sname"] for i, s in enumerate(shs)
                  if s["sname"] in SECTIONS}
    extent = {s["sname"]: (s["addr"], s["size"]) for s in shs
              if s["sname"] in SECTIONS}

    funcs = {s: [] for s in SECTIONS}
    for name, value, size, typ, shndx in symbols(elf_path):
        if typ == STT_FUNC and shndx in section_of and is_function(name):
            funcs[section_of[shndx]].append([value, size, name])

    # splat's .s files carry no .size, so fall back to the next function start
    for sec, lst in funcs.items():
        lst.sort()
        starts = [e[0] for e in lst]
        end = extent[sec][0] + extent[sec][1]
        for i, entry in enumerate(lst):
            if entry[1] == 0:
                nxt = bisect.bisect_right(starts, entry[0])
                entry[1] = (starts[nxt] if nxt < len(starts) else end) - entry[0]
    return funcs, extent


def stub_names(src_dir):
    """Functions still standing in as `#pragma GLOBAL_ASM`."""
    pragma = re.compile(r'^\s*#pragma\s+GLOBAL_ASM\("[^"]*/([^"/]+)\.s"\)')
    names = set()
    for root, _dirs, files in os.walk(src_dir):
        for fn in files:
            if fn.endswith(".c"):
                with open(os.path.join(root, fn), encoding="utf-8") as fh:
                    for line in fh:
                        match = pragma.match(line)
                        if match:
                            names.add(match.group(1))
    return names


def c_tu_names(build_src):
    """Functions defined by an object built from a C translation unit."""
    names = set()
    for root, _dirs, files in os.walk(build_src):
        for fn in files:
            if not fn.endswith(".o"):
                continue
            for name, _v, _sz, typ, shndx in symbols(os.path.join(root, fn)):
                if typ == STT_FUNC and shndx not in (SHN_UNDEF, SHN_COMMON) \
                        and is_function(name):
                    names.add(name)
    return names


def main(root):
    elf_path = os.path.join(root, "conker", "build", "conker.us.elf")
    if not os.path.isfile(elf_path):
        sys.exit("no %s -- build first (make -C conker --jobs)" % elf_path)

    funcs, extent = collect_functions(elf_path)
    stubs = stub_names(os.path.join(root, "conker", "src"))
    from_c = c_tu_names(os.path.join(root, "conker", "build", "src"))

    header = "%-10s %17s %8s %21s %8s" % ("section", "functions", "pct",
                                          "bytes", "pct")
    print(header)
    print("-" * len(header))
    totals = [0, 0, 0, 0]
    for sec in SECTIONS:
        lst = funcs[sec]
        done = [e for e in lst if e[2] in from_c and e[2] not in stubs]
        n_all, n_done = len(lst), len(done)
        b_all = sum(e[1] for e in lst)
        b_done = sum(e[1] for e in done)
        print("%-10s %7d /%8d %7.2f%% %10d /%10d %7.2f%%"
              % (sec[1:], n_done, n_all, 100.0 * n_done / n_all,
                 b_done, b_all, 100.0 * b_done / b_all))
        totals = [totals[0] + n_done, totals[1] + n_all,
                  totals[2] + b_done, totals[3] + b_all]
    print("-" * len(header))
    print("%-10s %7d /%8d %7.2f%% %10d /%10d %7.2f%%"
          % ("TOTAL", totals[0], totals[1], 100.0 * totals[0] / totals[1],
             totals[2], totals[3], 100.0 * totals[2] / totals[3]))

    every = {e[2] for lst in funcs.values() for e in lst}
    decompiled = (every & from_c) - stubs
    handwritten = every - from_c - stubs
    print()
    print("decompiled to C          %5d" % len(decompiled))
    print("still #pragma GLOBAL_ASM %5d" % len(every & stubs))
    print("handwritten .s objects   %5d" % len(handwritten))
    print("                         -----")
    print("total real functions     %5d" % len(every))
    if len(decompiled) + len(every & stubs) + len(handwritten) != len(every):
        sys.exit("classification does not partition the function set")
    orphans = stubs - every
    if orphans:
        print("\nWARNING: %d GLOBAL_ASM stubs are not in the linked ELF: %s"
              % (len(orphans), ", ".join(sorted(orphans)[:5])))

    print("\nshare of each section that sits inside a function:")
    for sec in SECTIONS:
        inside = sum(e[1] for e in funcs[sec])
        print("  %-9s %9d / %9d bytes  %6.1f%%"
              % (sec[1:], inside, extent[sec][1],
                 100.0 * inside / extent[sec][1]))


if __name__ == "__main__":
    main(sys.argv[1] if len(sys.argv) > 1 else ".")
