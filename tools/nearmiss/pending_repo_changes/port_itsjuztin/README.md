# Ported from github.com/itsjuztin/conker (2026-10-04)

10 of 12 ported and ROM-verified. NOT ported (their C needs banned forcers in our tree):
- func_16000590 (debugger/debugger): empty `if (!arg0) {}` in the loop (51 without) + `(s1 & 0xFFFFFFFF)`.
- func_16001BB4 (_Printf, debugger_257350): `char pad[12]` (91 without), `(c ^ 0) == %` (1), dummy
  `scan_next: ;` label (36); loop rotation gives 20. Its rodata (hlL, flag tables, pows) stays in
  block 2593B0, so it can still ship alone later.
Versions with those forcers kept here for reference only.

UPDATE 2026-10-05: func_16001BB4 (_Printf) now matches WITHOUT forcers -- verbatim SDK xprintf.c with
u8 chars and the SDK's declaration order (s, c, t before ac). Live in conker/src/debugger_257350.c.
