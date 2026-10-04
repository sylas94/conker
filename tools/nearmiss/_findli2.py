"""Widened: NON-VACUOUS hoists only.  A matched function of >= 12 instructions where
`addiu $v0,$zero,K` appears in the first few instructions AND there are branches after it,
i.e. the hoist actually moved the constant away from the return.  Also report whether $v0 is
redefined later (if it is, the constant is not the return value and the hit is spurious).
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
    if len(ins) < 12:
        continue
    for i, (op, args) in enumerate(ins[:6]):
        if op == "addiu" and args.startswith("$v0, $zero,"):
            nbr = sum(1 for op2, _ in ins[i+1:] if BR.match(op2))
            redef = sum(1 for j, (op2, a2) in enumerate(ins) if j > i and a2.startswith("$v0,")
                        and op2 in ("addiu", "or", "move", "lw", "lbu", "lh", "lhu", "mfc1", "li"))
            if nbr > 0:
                hits.append((tu, fn, i, len(ins), nbr, redef))
            break

print("MATCHED, len>=12, `li $v0,K` in first 6 insns, with branches after: %d" % len(hits))
print("%-18s %-18s %-5s %-6s %-8s %s" % ("tu", "func", "at", "len", "brs_after", "v0_redefs_after"))
for h in sorted(hits, key=lambda x: x[5])[:16]:
    print("%-18s %-18s %-5d %-6d %-8d %d" % h)
clean = [h for h in hits if h[5] == 0]
print("\nGENUINE (v0 never redefined after the hoist -- constant IS the return value): %d" % len(clean))
for h in clean[:10]:
    print("   %s / %s   len=%d" % (h[0], h[1], h[3]))
