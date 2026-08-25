"""Find MATCHED functions whose golden asm contains the delay-slot-family construct.

If a function is already byte-perfect and its golden asm has a `b` to the label that is
literally the next instruction (branch + delay slot + label), then its C source is a WORKED
EXAMPLE of the construct five parked near-misses are missing.  That is evidence the permuter
could never supply.
"""
import os, re, glob, collections

REPO = r"C:\Users\ssyla\OneDrive\Desktop\conker\conker decomp\conker"

# 1. which functions are still pragmas (i.e. NOT matched)
unmatched = set()
for pat in ("src/*.c", "src/*/*.c", "src/*/*/*.c"):
    for f in glob.glob(os.path.join(REPO, pat)):
        try:
            txt = open(f, encoding="utf-8", errors="replace").read()
        except Exception:
            continue
        for m in re.finditer(r'GLOBAL_ASM\("asm/nonmatchings/([^/]+)/([^"]+)\.s"\)', txt):
            unmatched.add((m.group(1), m.group(2)))

hits_b, hits_likely = [], []
total_matched = 0

for sfile in glob.glob(os.path.join(REPO, "asm", "nonmatchings", "*", "*.s")):
    tu = os.path.basename(os.path.dirname(sfile))
    fn = os.path.basename(sfile)[:-2]
    if (tu, fn) in unmatched:
        continue
    total_matched += 1
    lines = open(sfile, encoding="utf-8", errors="replace").read().split("\n")
    # keep only instruction lines and label lines, in order
    seq = []
    for ln in lines:
        mi = re.match(r"\s*/\*[^*]*\*/\s+(\S+)\s*(.*)$", ln)
        if mi:
            seq.append(("i", mi.group(1), mi.group(2).strip()))
            continue
        ml = re.match(r"\s*(\.L[0-9A-Fa-f]+):", ln)
        if ml:
            seq.append(("l", ml.group(1), ""))
    for i, item in enumerate(seq):
        if item[0] != "i":
            continue
        op, args = item[1], item[2]
        # redundant unconditional branch: b LBL ; <delay slot> ; LBL:
        if op == "b" and args.startswith(".L"):
            tgt = args.split()[0]
            if i + 2 < len(seq) and seq[i+1][0] == "i" and seq[i+2][0] == "l" and seq[i+2][1] == tgt:
                hits_b.append((tu, fn, i, seq[i+1][2]))
        # branch-likely whose delay slot duplicates the instruction at the target
        if op in ("beql", "bnel", "beqzl", "bnezl", "bgezl", "blezl") and ".L" in args:
            tgt = args.split(",")[-1].strip()
            if i + 1 < len(seq) and seq[i+1][0] == "i":
                slot = seq[i+1]
                for j, it2 in enumerate(seq):
                    if it2[0] == "l" and it2[1] == tgt:
                        if j + 1 < len(seq) and seq[j+1][0] == "i" and \
                           seq[j+1][1] == slot[1] and seq[j+1][2] == slot[2]:
                            hits_likely.append((tu, fn, slot[1], slot[2]))
                        break

print("matched functions scanned: %d" % total_matched)
print("\n=== MATCHED functions with a redundant `b` to the next label: %d ===" % len(hits_b))
c = collections.Counter(t[0] for t in hits_b)
for tu, n in c.most_common(12):
    ex = [h for h in hits_b if h[0] == tu][:1][0]
    print("   %-18s %3d   e.g. %s  slot=%s" % (tu, n, ex[1], ex[3][:34]))
print("\n=== MATCHED functions with a branch-likely duplicating the target insn: %d ===" % len(hits_likely))
c2 = collections.Counter((t[0], t[1]) for t in hits_likely)
for (tu, fn), n in c2.most_common(10):
    print("   %-18s %-16s %d" % (tu, fn, n))
