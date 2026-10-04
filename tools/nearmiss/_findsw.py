"""Narrow the 87 hits to the exact worked example the eeprom pair needs: a MATCHED function
whose dispatch is switch-style (ori $at,$zero,K ; beq $rX,$at,.Lbody -- forward branch to a
case body) AND which still ends a case body with a redundant `b` to the next label.
"""
import os, re, glob

REPO = r"C:\Users\ssyla\OneDrive\Desktop\conker\conker decomp\conker"
unmatched = set()
for pat in ("src/*.c", "src/*/*.c", "src/*/*/*.c"):
    for f in glob.glob(os.path.join(REPO, pat)):
        try:
            txt = open(f, encoding="utf-8", errors="replace").read()
        except Exception:
            continue
        for m in re.finditer(r'GLOBAL_ASM\("asm/nonmatchings/([^/]+)/([^"]+)\.s"\)', txt):
            unmatched.add((m.group(1), m.group(2)))

hits = []
for sfile in glob.glob(os.path.join(REPO, "asm", "nonmatchings", "*", "*.s")):
    tu = os.path.basename(os.path.dirname(sfile))
    fn = os.path.basename(sfile)[:-2]
    if (tu, fn) in unmatched:
        continue
    seq = []
    for ln in open(sfile, encoding="utf-8", errors="replace").read().split("\n"):
        mi = re.match(r"\s*/\*[^*]*\*/\s+(\S+)\s*(.*)$", ln)
        if mi:
            seq.append(("i", mi.group(1), mi.group(2).strip())); continue
        ml = re.match(r"\s*(\.L[0-9A-Fa-f]+):", ln)
        if ml:
            seq.append(("l", ml.group(1), ""))
    # switch dispatch: >=2 `beq $rX, $at, .L` whose targets appear LATER (forward)
    labels = {it[1]: j for j, it in enumerate(seq) if it[0] == "l"}
    fwd_beq = 0
    for j, it in enumerate(seq):
        if it[0] == "i" and it[1] == "beq" and "$at," in it[2] and ".L" in it[2]:
            tgt = it[2].split(",")[-1].strip()
            if labels.get(tgt, -1) > j:
                fwd_beq += 1
    if fwd_beq < 2:
        continue
    # redundant b to the very next label
    red = []
    for j, it in enumerate(seq):
        if it[0] == "i" and it[1] == "b" and it[2].startswith(".L"):
            tgt = it[2].split()[0]
            if j + 2 < len(seq) and seq[j+1][0] == "i" and seq[j+2][0] == "l" and seq[j+2][1] == tgt:
                red.append(seq[j+1][2])
    if red:
        hits.append((tu, fn, fwd_beq, len(red), red))

print("MATCHED functions with switch-style forward dispatch AND a redundant `b`: %d" % len(hits))
for tu, fn, nb, nr, slots in sorted(hits, key=lambda h: -h[3])[:10]:
    print("   %-16s %-16s fwd_beq=%d  redundant_b=%d  slots=%s" % (tu, fn, nb, nr, slots[:2]))
