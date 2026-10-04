"""func_150C7670's park asks: enumerate MATCHED functions whose golden hoists `li $v0,K` into
the ENTRY block (before any branch) even though the value is only used at the return, and
check whether they all contain a source-level if/else.
"""
import os, re, glob

REPO = r"C:\Users\ssyla\OneDrive\Desktop\conker\conker decomp\conker"
unmatched, srcof = set(), {}
for pat in ("src/*.c", "src/*/*.c", "src/*/*/*.c"):
    for f in glob.glob(os.path.join(REPO, pat)):
        try:
            txt = open(f, encoding="utf-8", errors="replace").read()
        except Exception:
            continue
        for m in re.finditer(r'GLOBAL_ASM\("asm/nonmatchings/([^/]+)/([^"]+)\.s"\)', txt):
            unmatched.add((m.group(1), m.group(2)))
        srcof[os.path.basename(f)[:-2]] = f

BR = re.compile(r"^(b|beq|bne|beqz|bnez|bgez|blez|bgtz|bltz|j|jal|jalr|beql|bnel|beqzl|bnezl|bgezl|bltzl)")
hits = []
for sfile in glob.glob(os.path.join(REPO, "asm", "nonmatchings", "*", "*.s")):
    tu = os.path.basename(os.path.dirname(sfile))
    fn = os.path.basename(sfile)[:-2]
    if (tu, fn) in unmatched:
        continue
    ins = []
    for ln in open(sfile, encoding="utf-8", errors="replace").read().split("\n"):
        mi = re.match(r"\s*/\*[^*]*\*/\s+(\S+)\s*(.*)$", ln)
        if mi:
            ins.append((mi.group(1), mi.group(2).strip()))
    if not ins:
        continue
    # index of first branch/jump
    firstbr = next((i for i, (op, _) in enumerate(ins) if BR.match(op)), len(ins))
    # `addiu $v0, $zero, K` in the entry block
    for i, (op, args) in enumerate(ins[:firstbr]):
        if op == "addiu" and args.startswith("$v0, $zero,"):
            # and $v0 must not be redefined later except at return -> crude: count defs
            defs = sum(1 for op2, a2 in ins if a2.startswith("$v0,") and op2 in ("addiu", "or", "move", "lw", "li"))
            hits.append((tu, fn, i, firstbr, len(ins), defs))
            break

print("MATCHED functions hoisting `addiu $v0,$zero,K` into the entry block: %d" % len(hits))
print("%-18s %-18s %-6s %-8s %-6s %s" % ("tu", "func", "at", "firstbr", "len", "v0defs"))
for tu, fn, i, fb, n, d in sorted(hits, key=lambda h: h[4])[:14]:
    print("%-18s %-18s %-6d %-8d %-6d %d" % (tu, fn, i, fb, n, d))
