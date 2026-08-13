# func_151CA6A0 — 1068 B, game_1F4650.c — parked at **asm-differ 517** (honest)

## WAVE 2026-08-13 (d) — BAIL RE-CONFIRMED a FIFTH time. The two levers this wave was aimed at
## are now CLOSED BY MEASUREMENT, and the "what real value does the missing web hold?" question
## has an answer: **the binary cannot tell a named variable from `+= 0`.**

Base re-verified through `make` + `tools/buildlock.sh`: **517 with -R and 517 without -R**, 267
instructions, and the pragma-in repo TU rebuilds to **0/0**. A private parallel scorer was
calibrated against both (pragma-in => 0 @ 267; parked base => 517 @ 267, and it reproduces the
parked object's `.text` sha1 exactly) before any variant was believed.

### (1) THE UNUSED-PARAMETER LEVER IS UNAVAILABLE HERE — proved by instruction count, not argument

The wave's lever says "IDO homes every integer register parameter at entry whether or not it is
read, and those homes are in the incoming-argument area, NOT the local area". **The first half of
that is true and the second half is what kills it here**: the home store is a real instruction.

| prototype | prologue | insns | score |
|---|---|---|---|
| `func_151CA6A0(void *arg0, u8 arg1)` (parked) | `sw a0,0xf8(sp)` / `sw a1,0xfc(sp)` | **267** | **517** |
| `+ s32 arg2` (never read) | `… sw a2,0x100(sp)` | 268 | 617 |
| `+ s32 arg2, s32 arg3` | `… sw a2,0x100 / sw a3,0x104` | 269 | 717 |
| `+ s32 sz` used as the 0x58 size carrier at all 10 sites | `… sw a2,0x100(sp)` | 268 | 617 |

Golden's prologue is `sw a0,0xf8(sp)` then `sw a1,0xfc(sp)` and **nothing else** (rows 9-10 of the
diff), and golden is 267 instructions. So an unused third parameter is *excluded by the binary*:
it would cost exactly the one instruction the function does not have. The parameter list is
closed at two. (The two callers agree — `func_151C9BA0` at 151C9C58 and 151C9DB8 both set only
`a0` and `a1`; `a2` merely holds a stale `1` left over from the preceding `func_151C9F38` call,
which is not evidence of a third argument.)

### (2) THE INT-WIDTH CARRIER: 15 REAL VALUES TRIED IN THE 4th SCALAR SLOT

The frame *does* admit a 4th scalar declared last (`roundup8(52+196) = 248`, offsets of
`temp_v0`/`temp_type`/`i` at 0x40/0x3C/0x38 preserved; verified `addiu sp,sp,-248` in every row
below). The previous wave tried four values; this wave tried fifteen, each wired to *all* of its
natural use sites (and, for three of them, initialised late instead of early):

| carrier (declared last), used at every natural site | score | insns |
|---|---|---|
| `s32 size = 0x58` (helper arg 5 + `memcpy` size, 10 uses) | **517** | 267 |
| `s32 size` at the helper only (5 uses) | **517** | 267 |
| `s32 alpha = 0xFF` (5 uses) / `s32 one = 1` (5 uses) | **517 / 517** | 267 |
| the same three initialised late (just before block 3) | **517 / 517 / 517** | 267 |
| `s32 seven = 7` (the loop call's type argument) | **517** | 267 |
| `s32 off = 0x70` (the `memcpy` destination offset, 5 uses) | **517** | 267 |
| `s32 mask = ~0x6` (4 uses) | **517** | 267 |
| `u16 f16 = 0x58` / `void *pay = &sp44` / `void *desc = &spA0` | **517 / 517 / 517** | 267 |
| `s32 count = 12` (the loop bound) | 1332 | 269 |
| `s32 flag = D_80082FA0` | 1293 | 267 |
| `s32 bits = (1 << (k+0xB)) \| 0x50` | 6471 | 262 |
| `s32 shift = k + 0xB` | 7369 | 263 |
| `s32 kind = *(u8*)(arg0+0x23D)` | 7984 | 258 |
| `u8 temp_type` / `u32 temp_type` / `s16 temp_type` | 957 / **517** / **517** | 263 / 267 / 267 |

Ten of the fifteen are **byte-identical to the base** (`.text` sha1 `8de865e242…`). An int-width
carrier holding a real value is simply inert here — IDO constant-propagates it away and the local
occupies its home without consuming a temp web.

### (3) THE `quad` VARIABLE — the strongest form of the 172 hypothesis, and it is REFUTED

The sharpest statement the previous wave left was: *"the missing web is probably real and probably
came from a parameterised source idiom instantiated with k = 0"*. This wave built exactly that
idiom out of a **named local holding the real value**:

```c
    s32 quad;                       /* the 2-bit corner/alignment code */
    ...
    quad = 0x6;  spA0.unk14 &= ~0x6;  spA0.unk14 |= quad;   /* block 1 */
    quad = 0x4;  spA0.unk14 &= ~0x6;  spA0.unk14 |= quad;   /* block 2 */
    quad = 0x0;  spA0.unk14 &= ~0x6;  spA0.unk14 |= quad;   /* block 3 */
    quad = 0x2;  spA0.unk14 &= ~0x6;  spA0.unk14 |= quad;   /* block 4 */
```

It scores **172 at 267 instructions** — the best number this function has ever reached. It is
still **REFUSED**, and this time the refutation is airtight rather than a judgement call:

```
              score insns  .text sha1 of func_151CA6A0's disassembly
spA0.unk14 |= 0x0;                 172  267  50ece708e1cc698e
spA0.unk14 += 0;                   172  267  50ece708e1cc698e
spA0.unk14 |= (0 << 1);            172  267  50ece708e1cc698e
spA0.unk14 |= (spA0.unk14 & 0x0);  172  267  50ece708e1cc698e
spA0.unk14 ^= 0x0;                 172  267  50ece708e1cc698e
quad = 0; ... |= quad;  (block 3)  172  267  50ece708e1cc698e
quad, all four blocks              172  267  50ece708e1cc698e
```

**Seven mutually-exclusive spellings, one identical object.** The named variable is not a
different construct — it *is* `+= 0` wearing a name, and the binary cannot distinguish them. The
N-NO-OPS TEST fires exactly as before. Two further checks close it:

* `quad` typed `u8` / `u16` / `s16` / `u32`, and declared in any of the four slot positions, and
  assigned *after* the mask instead of before — **all 172, all byte-identical**.
* written in the COMBINED form `spA0.unk14 = (spA0.unk14 & ~0x6) | quad;` at all four blocks it
  scores **1413 at 265 instructions** — *exactly* the previous wave's number for the combined form
  with literals. So IDO folds `quad` away completely; there is no `quad` web in the object at all.
  The 172 comes solely from the existence of a separate statement whose value is zero.

So the honest answer to "what REAL value does the extra temp web hold?" is: **the binary does not
say, and cannot say.** Any statement at that point supplies the web; none of them is evidenced.

### (4) Block 5, re-swept on the 172 base (in case the forcer unlocked the other residual)

29 orderings of block 5's nine independent units run on the **quad/172** base: minimum **172**
(the identity ordering), everything else 420–1950. So even granting the forcer, block 5's group
permutation does not become reachable. This kills the last "maybe they interact" argument.

### Axes varied this wave vs axes not varied (the seven-axis rule)

Varied: **4 TYPE/WIDTH** (carrier types, `temp_type` u8/u32/s16), **5 SCOPE/DECL** (4th scalar in
four declaration positions, carrier init early vs late), **7 REFCOUNT** (15 distinct carriers, each
at one site and at all sites), **3 SHAPE** (split vs combined with a variable, assignment before vs
after the mask), **2 ORDER** (29 block-5 orderings on the new base), and the **prototype/ABI** axis
that four previous waves had *not* touched (parameter count — now closed by the homing law).
**Not varied:** the callee prototypes and the struct layouts (fixed by the byte-perfect sibling
`func_150CF680` and by the frame/offset decode), and the FP-literal spellings (closed in wave b).

**The call stands, now five times over: stop spending waves on func_151CA6A0.** The parked file is
honest, semantically correct, instruction-count exact (267), frame- and offset-exact.

---

## WAVE 2026-08-13 (c) — BAIL RE-CONFIRMED a fourth time, and one PRIOR ARGUMENT CORRECTED

436 fresh variants through a calibrated private scorer (pragma-in => 0, parked base reproduces
517 exactly); re-verified through `make` + `tools/buildlock.sh`: **517 with -R and 517 without
-R**, restored TU => 0/0. Every one of the 436 is 517 or worse. Instruction count 267 throughout.

### The two mechanisms this wave was pointed at are BOTH already satisfied by the parked file

**(a) "a binding that spans both arms of an `if` becomes one long-lived web."** The parked file
binds `temp_type` across both arms at four sites. Confining it to one arm is strictly WORSE, and
at the first site it *loses an instruction* — i.e. the binary positively evidences the both-arms
form:

| variant | score | insns |
|---|---|---|
| `temp_type = 0; if (arg1) temp_type = 4;` (all 4 sites) | 7909 | 269 |
| `temp_type = 4; if (!arg1) temp_type = 0;` (all 4 sites) | 9014 | 269 |
| one-arm at site 0 only | 682 | **266** |
| one-arm at sites 1 / 2 / 3 | 2456 / 2461 / 2461 | 269 |
| a 6th local bound across both arms of the block-5 `D_80082FA0 == 1` tests (unk18 / unk20 / both) | 587 / 862 / 882 | 267 / 266 / 266 |
| the block-5 tests written one-armed (`= -50.0f; if (…) = -62.0f;`) | 1157 / 902 | 266 |
| block 1's `unk10` one-armed, and as a both-arms 6th local | 1052 / 1382 | 266 |

**(b) the address-taken-local alias barrier** was closed by the previous wave (7 variants, all
byte-identical) and nothing new was found: `&spA0` and `&sp44` are already address-taken (they
are passed to the helper and to `memcpy`), which is exactly why *no* store in this function is
dead-store-eliminated. There is no second barrier to add.

Also measured and rejected: the `memcpy` written as a **struct assignment**
(`*(struct_151CA6A0_sp44 *)((u8 *)temp_v0 + 0x70) = sp44;`) — IDO inlines the copy instead of
calling the helper: 2147–7012 at 279–285 instructions per site, 15474 at 333 for all five.
And SCOPE (axis 5): `i` declared in an inner block around the loop is **517, byte-identical**.

### The block-5 order sweep, re-run on the honest base over ALL TWELVE units

The previous wave only re-ran the five opening stores on the honest base. This wave swept all
twelve independent units of block 5 (`unk0 unk4 unkC unk8 unk10 unk14 unk30 unk34 / sp44.unk28 /
the two D_80082FA0 ifs / sp44.unk1C`): every unit moved to every position (144) plus 265 random
permutations = **409 orderings, minimum 517, 18 tied at 517**. Note the corollary: block 5's
order is *not* globally canonicalised (391 of 409 orderings score worse) — only the five opening
stores are. 517 is a genuine floor of that axis, not a plateau artefact.

### CORRECTION to the previous wave's honesty argument (it refuted the wrong family)

The 2026-08-12(b) entry concluded the "uniform family" reading was *refuted* because the uniform
**combined** shape `(x & ~6) | k` does not reproduce the codegen for k = 0. That refutation is
aimed at the wrong family. Block 1 is provably the **split** form (it emits three `sh` to
0x180(sp) — rows 64, 79, 81 — and combining it costs 2 instructions and 866 points), so the
family the binary evidences is the SPLIT one, `f &= ~6; f |= k;`, and its k = 0 member is
`f |= 0x0` — the very statement that scores 172. Measured this wave to make the point concrete:

| variant | score | insns |
|---|---|---|
| all four blocks through one macro `SETQUAD(f,k){ (f) &= ~0x6; (f) \|= (k); }`, k = 6/4/**0**/2 | **172** | 267 |
| the same macro with block 3 written bare instead | 517 | 267 |

**This changes the argument but NOT the verdict, and the 172 is still REFUSED.** The macro form
produces a byte-identical object to the bare `spA0.unk14 |= 0x0;`, so it is the same construct in
different clothes and it adds no new evidence. The N-NO-OPS TEST still fires exactly as before:
`|= 0x0`, `+= 0`, `|= (0 << 1)` and `|= (spA0.unk14 & 0x0)` all reach 172 identically, so the
binary evidences only "one extra folded temp web exists here" and cannot name the construct. What
a future wave should take from this is the narrower statement: *the missing web is probably real
and probably came from a parameterised source idiom instantiated with k = 0* — but no honest
source text has been found that supplies it, and a no-op must not be shipped to fake it.

Four further block-3 spellings measured and flat at 517: `(u16)(x & (u16)~0x6)`, `&= ~0x00000006`,
`&= 0xFFF9U`, `& ~(0x4 | 0x2)`.

### Axes varied vs axes not varied (the cookbook's bail rule)

Varied across four waves: 1 SPELLING (~150), 2 ORDER (409 this wave alone, plus the earlier 273),
3 SHAPE (both-arms vs one-arm bindings, guard-side placement, assignment-in-condition, hoisted
destination), 4 TYPE/WIDTH (`u16`/`s16`/`s32`/`u8`/`s8` on `unk14`, `void*`/`s32` on `temp_v0`,
bitfields, array members), 5 SCOPE (file-scope typedefs, inner-block `i`), 7 REFCOUNT (5th and 6th
locals, cached `D_80082FA0`, cached masks). Axis 6 LINE placement was swept in an earlier wave.
**Not varied: the callee prototypes and the struct layouts** — both are fixed by the byte-perfect
sibling `func_150CF680` and by the frame/offset decode, so there is nothing to vary there.

The call stands: **stop spending waves on func_151CA6A0.**

---

## WAVE 2026-08-13 (b) — BAIL RE-CONFIRMED. Four more axes closed; the matched sibling agrees.

Still **517 at 267 instructions**. This wave deliberately avoided the ~400 variants already on
record and went after four axes no previous wave touched. **All of them are inert or worse.**

### The matched sibling proves the idiom is already right

`func_150CF680` (src/game_FC5F0.c:132) is a **live, matched (score 0)** caller of the same
helper, and its shape is character-for-character the shape parked here:

```c
    void *temp_v0;
    ...
    temp_v0 = func_1515548C(&sp40, 0xC, 0, 0, 0x10, arg1, arg2);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x70, &sp30, 0x10);
    }
```
Its struct is the same 0x58-byte layout with the same field names, declared at **file** scope.
So the `void *temp_v0` / `!= NULL` / `(u8 *)temp_v0 + 0x70` / `memcpy` idiom is confirmed from a
byte-perfect function, not inferred — there is nothing left to guess there.

### The four new axes, all measured (267 instructions in every row)

| axis | n | result |
|---|---|---|
| the two function-local `typedef struct`s hoisted to **file scope** (as the matched sibling declares them) | 1 | **517**, byte-identical |
| `arg0` given a real struct type and `*(u8 *)((s32)arg0 + 0x23D)` written `arg0->unk23D` | 1 | **517**, byte-identical |
| `(1 << (x + 0xB)) \| 0x50` spellings: `+ 11`, `0x50 \| (…)`, `(s32)1 <<`, `0xB + x` | 4 | **517**; `+ 0x50` instead of `\| 0x50` **907** |
| block-5 statement placement re-run on the HONEST base: `sp44` group ahead of the `spA0` group; first `if` block ahead; `sp44.unk28` ahead; `unk30`/`unk34` moved late; `unk10` first; `unk14` first | 6 | **5568 / 2727 / 1077 / 1442 / 517 / 1170** |
| `if (D_80082FA0 != 1)` with the two branches swapped (both sites) | 1 | **947** |
| `memcpy` size and the helper's size argument written `88` instead of `0x58` | 2 | **517** |

`g_b5_unk10_first` scoring 517 **byte-identical** reconfirms from a fresh angle what the previous
wave's 120-permutation sweep found: IDO *canonicalises* block 5's opening stores, so their source
order is not observable at all, and the 16-row block-5 scheduling residual has no source handle.

### The block-5 residual, read precisely

Golden emits, at the head of block 5, one instruction mine defers by 14 slots:

```
 GOLD 380c  li v1,1          <- the constant for BOTH `D_80082FA0 == 1` tests, hoisted to the head
 GOLD 3818  swc1 $f2,0xa0    MINE 3814  sb   t7,0xb0     <- and then the three constant groups
 GOLD 381c  swc1 $f2,0xa4    MINE 3818  swc1 $f0,0xac       come out in the REVERSE group order
 GOLD 3820  swc1 $f0,0xac    MINE 381c  swc1 $f0,0xa8       (mine: sb, 3.0f pair, 0.0f pair;
 GOLD 3824  swc1 $f0,0xa8    MINE 3820  swc1 $f2,0xa0        golden: 0.0f pair, 3.0f pair, sb)
 GOLD 3828  sb   t1,0xb0     MINE 3824  swc1 $f2,0xa4
                             MINE 3848  li   v1,1
```
Within each group the order is identical; only the group order and the `li v1,1` position differ.
Moving the two `D_80082FA0 == 1` tests (which are what create the `1` web) earlier in block 5 is
1077–5568, i.e. strictly worse — so the hoist is not reachable from statement order either.

### Verdict (unchanged, now with four more closed axes)

**Stop spending waves on func_151CA6A0.** The parked file is honest, semantically correct,
instruction-count exact (267), frame- and offset-exact, and matches a byte-perfect sibling's
idiom. The residual is 41 rows: 28 of a one-web $t-rotation and 13 of the block-5 group
permutation, neither of which any of ~430 measured source variants across four waves can touch.

## WAVE 2026-08-13 — BAIL CONFIRMED. The alias-barrier hypothesis is now closed too.

Still **517**. This wave was pointed at the one hypothesis the residual actually suggests —
"golden spends one temp-register web and emits no instruction; what REAL value does it hold?
an address-taken local, a hoisted read, something the guard-side lever would move" — and
tested it directly. **All seven variants are byte-identical to the base at 517.**

| variant | score |
|---|---|
| `u16 *pflags = &spA0.unk14;` (6th local, declared LAST so every offset is preserved), all four masks written `*pflags &= ~0x6; *pflags \|= k;` | **517** |
| the same, used at block 3 only | **517** |
| `struct_151CA6A0_spA0 *p = &spA0;` (6th local), the four masks written `p->unk14 ...` | **517** |
| `void *src = &sp44;` (6th local), every `memcpy` source written `src` | **517** |
| `if ((temp_v0 = func_1515548C(...)) != NULL)` — assignment inside the condition, all five sites | **517** |
| `dst = (u8 *)temp_v0 + 0x70;` computed BEFORE the guard, all five sites | **517** |
| block 3's mask written `spA0.unk14 = spA0.unk14 & ~0x6;` (explicit read-modify-write) | **517** |

The first four matter most: the cookbook's strongest lever for "a value that exists but emits
nothing" is the **address-taken local as an alias barrier**, and it is completely inert here —
IDO folds `p = &spA0; p->unk14` into direct frame addressing and consumes no web at all. That
was the last structurally-motivated candidate. Combined with the ~400 variants below, the call
stands: **stop spending waves on func_151CA6A0.** Confirmed the parked file still scores 517
and that the repo TU restores to 0 with the pragma in.

## WAVE 2026-08-12 (c) — BAIL. The missing web has no source-level handle.

Still 517. ~170 further honest variants this wave, **every single one exactly 517 or worse**,
plus a decomp-permuter run (1100+ iterations, frame- and offset-gated) whose *only*
improvements are the banned no-op shape. The evidence is now conclusive enough to stop.

### The permuter localised the web, and then refuted itself

The permuter's three improving outputs are all the SAME construct — `if ((temp_v0 != 0) != 0)`,
a semantically-inert doubled comparison — applied at three DIFFERENT `if (temp_v0 != NULL)`
guards, scoring **277 / 327 / 367**. Combined with the previous wave's four no-ops at block 3
all tying at **172**, that is seven mutually-exclusive no-op statements at four sites producing
four different scores. Per the N-NO-OPS TEST the binary is evidencing "extra folded temp webs
exist near here" and nothing about any source construct. Ship none.

What it *did* buy is a location: the best forcer site is block 3's mask (172), the second is
**block 2's guard**, immediately before block 3 — which is exactly where the one-web offset
first becomes visible (`andi t7` vs `andi t5`).

### Everything honest tried at that location — all byte-identical to the base

| axis | n | result |
|---|---|---|
| guard spelling at block 2 AND at all five sites: `if (temp_v0)`, `!= 0`, `NULL != temp_v0`, `(s32)temp_v0 != 0` | 8 | **517, all** |
| memcpy destination spelling: `(void*)((s32)tv0+0x70)`, `&((u8*)tv0)[0x70]`, `((u8*)tv0)+0x70` | 6 | **517, all** |
| 5th local `u8 *dst` holding the destination (block 2 only, and all sites) | 2 | **517** |
| `temp_v0` declared `s32` instead of `void *`, with casts at every use | 1 | **517** |
| block-3 mask casts: `(s16)/(u16)/(s32)/(u32)` on the result, on `~0x6`, on the read | 12 | **517** (`(u8)` 532, `(s8)` 717) |
| block-3 shapes: `& ~6`, `& ~0x06`, mask before/mid/after the float pair | 5 | **517** (shift-form 847) |
| `temp_type` if/else: ternary, `= 0x4` | 2 | **517** (`if (arg1 != 0)` 1779 — reconfirms the u8-parameter law) |
| loop form `i < 12` / `++i` | 2 | **517** |
| **all 120 permutations of block 5's five opening stores, RE-RUN on the honest base** | 120 | **517, every one** |

That last row matters: the previous wave's 273-variant block-5 sweep was run on the now-void
**forced** base, so it was worth re-running. It reproduces exactly. IDO *canonicalises* those
five independent stores — source order is not observable at all — which is why the block-5
scheduling residual is not a statement-order problem either.

### The frame has room for a 5th local, and it buys nothing

The old NOTES said "no room for a cached `D_80082FA0` or any other extra local". That was
wrong — its own calibration says adding one scalar keeps 248, and I re-measured it directly
(`frame=-0xf8` with a dead 5th scalar, and with `u16 flags`, and with `s32 mode`). So the axis
was open. It is now closed by measurement, not by arithmetic:

* dead 5th scalar — **517**, byte-identical (an unreferenced local really is inert here)
* `u16 flags` / `s32 flags` holding the block-3 mask result — **517**, byte-identical
* `s32 mode = D_80082FA0;` hoisted, both `if`s reading `mode` — **537** (early) / **537** (late)
* `s32 kind = *(u8*)(arg0+0x23D);` in block 5 — **692**

### Verdict

Residual is 28 register-only rows plus a 16-row block-5 scheduling permutation that is
provably insensitive to source order (120/120). Two *hundred* independent spellings across
three waves leave the score EXACTLY unchanged; only banned no-ops move it, and they disagree
with each other about where. This meets the cookbook's BAIL RULE. **Recommend: stop spending
waves on func_151CA6A0.** The parked file is honest, semantically correct, instruction-count
exact (267) and frame/offset exact; it is a good permanent near-miss record.


`tools/nearmiss/func_151CA6A0.c` is the WHOLE TU with this function live (pragma removed).
Drop it over `conker/src/game_1F4650.c` to resume. The repo copy of the TU is UNTOUCHED
(pragma still in place) — verified with `git status --short -- conker/src/game_1F4650.c`
(prints nothing).

## WAVE 2026-08-12 (b) — THE HONESTY QUESTION IS CLOSED: `|= 0x0` WAS A FORCER

The previous wave parked this at **172** on the back of `spA0.unk14 |= 0x0;` in block 3 — a
statement that emits no instruction and only re-aligns the register allocation — and left the
call to a later wave. **The call has now been made, by measurement, and it goes against the
forcer.** The forcer is dropped, the 172 is void, and the honest base is **517**.

### What was tested, and what it showed

The structural defence was: the four corner blocks poke a 2-bit alignment field as
`(x & ~6) | k` for k = 6, 4, 0, 2; three are forced by the binary; so the k=0 member should be
spelled uniformly with its siblings. **If that family is real, the uniform `(x & ~6) | k` shape
must reproduce the codegen for k=0. It does not.**

| variant | score | insns |
|---|---|---|
| `spA0.unk14 &= ~0x6;` alone (honest) | **517** | 267 |
| `spA0.unk14 = (spA0.unk14 & ~0x6) \| 0x0;` — the uniform shape | **517** | 267 |
| `= (spA0.unk14 & ~0x6) \| 0;` / `\| 0x00;` / `\| (0 << 1)` / `\| (0 & 0x6)` | **517** | 267 |
| `= (spA0.unk14 & 0xFFF9) \| 0x0;` | **517** | 267 |
| `= (u16)(spA0.unk14 & ~0x6);` and two other cast forms | **517** | 267 |
| `spA0.unk14 \|= 0x0;` (the forcer) | 172 | 267 |
| `spA0.unk14 += 0;` | 172 | 267 |
| `spA0.unk14 \|= (0 << 1);` | 172 | 267 |
| `spA0.unk14 \|= (spA0.unk14 & 0x0);` | 172 | 267 |

**IDO folds `| 0` inside an expression completely — no web is consumed — so the uniform
combined shape is byte-identical to just dropping the term.** The 172 is reachable *only*
through a separate no-op *statement*, and four different no-op statements reach it equally
well. So the binary does not evidence `| 0` at all; it evidences only "one more folded temp
register web here", and every construct that supplies one is banned.

### The uniform-family argument is not merely unproven — it is refuted

Making the four blocks genuinely uniform makes things **worse**, and two of those variants
lose two instructions (golden has 267):

| family shape | score | insns |
|---|---|---|
| all four `&= ~6; \|= k;` (current parked), block 3 bare | 517 | 267 |
| blocks 2+4 combined, block 3 bare | 587 | 267 |
| block 2 combined only, block 3 bare | 567 | 267 |
| blocks 2,3,4 combined | 587 | 267 |
| **all four combined** | **1413** | **265** |
| all four combined, block 3 bare | 1413 | 265 |
| block 1 combined only, block 3 bare | 1383 | 265 |

Block 1 is *provably* the split form (it is the only block that emits two `sh`; combining it
costs 2 instructions and 866 points). The binary rejects the uniform-combined family outright.

### The previous wave's "step 2" is worth ZERO without the forcer

The block-4 edit — splitting `= (x & ~6) | 2` into `&= ~6; |= 2;` — was credited with 345
points (477 → 172). Measured on the honest base, block 4 combined and block 4 split score
**517 and 517**: byte-identical. Its whole value was contingent on the banned statement. It is
kept in the parked file because it is honest and internally consistent with block 1, not
because it buys anything.

### Every other honest lever tried this wave (all measured, none beat 517)

| sweep | n | result |
|---|---|---|
| chained `unk0 = unk4 = -25.0f`, reversed chain, read-back `unk4 = unk0` | 6 | 517 / 525 |
| block-3 store order swap, mask before/mid/after the float pair | 4 | 517 / 525 |
| literal spelling `-25.f`, `-25.0e0f`, `-25.0` (double), `-25` (int), `(f32)-25.0` | 7 | 517 |
| `&= ~0x2; &= ~0x4;` two-bit split mask, `&= ~(0x2\|0x4)` | 2 | 527 / 517 |
| **bitfield**: `union { u16 unk14; struct { u16 hi:13, quad:2, lo:1; } b; }`, `b.quad = 0/1/2/3` | 5 | 1522 / 1757 / **4143** |
| **array members**: `f32 pos[2]; f32 size[2];`, `f32 v[4];`, pos-only, size-only | 10 | **byte-identical to scalars on both bases** |
| reversed comparison `if (1 == D_80082FA0)` (one, other, both) | 6 | 527 / 537 (honest), 182 / 192 (forced) |

Two of these close out the previous wave's "next moves": **arrays are completely inert here**
(all ten array variants are byte-identical to the scalar declaration, on both bases), and the
**bitfield reading is refuted** (a zero-valued bitfield store does *not* allocate-and-fold a
web; it costs 2 extra instructions and 1005+ points). The union declaration on its own is inert
(control scored 172 on the forced base), so those numbers are the bitfield *stores* talking.

## The residual at 517 — 28 register rows + the same 16 scheduling rows

Instructions 1–138 are byte-identical to golden. From 139 the whole difference is a **one-web
rotation offset**: golden's temp stream is exactly one position ahead of mine.

```
 139  GOLD andi t7,v0,0xfff9      MINE andi t5,v0,0xfff9      <- block 3's mask
 147  GOLD li   t1,88             MINE li   t7,88
 148  GOLD li   t8,255            MINE li   t1,255            <- mine[i] == golden[i-1]
 149  GOLD li   t6,1              MINE li   t8,1
 168  GOLD andi t0,v0,0xfff9      MINE andi t9,v0,0xfff9
 ...  (rows 139-182 and 239-244 are all of this one kind)
```

Golden spent one more temp web than an honest `&= ~0x6` produces, and it spent it with no
instruction to show for it. That is a real fact about the binary and it is worth recording —
but it does **not** identify the source construct, because four different banned no-ops supply
it identically.

Plus the unchanged block-5 residual (rows 196–217), a pure scheduling permutation:

```
 196  GOLD li v1,1                MINE lw t8,248(sp)
 199  GOLD swc1 $f2,160(sp)       MINE swc1 $f0,172(sp)
 ...  golden emits the five opening stores in EXACT SOURCE ORDER (160,164,172,168,176) and
      hoists `li v1,1` to the head; mine emits the three constant groups in REVERSE order
      (sb, then the 3.0f pair, then the 0.0f pair), preserving source order within each group.
```

## What is left, and what is NOT worth re-running

Do not re-explore: statement order in block 5 (every unit to every position + all 120
permutations of the five opening stores, 273 variants, previous wave), line joins, literal
spellings, declaration order, loop forms, array members, bitfields, comparison operand order,
`|= 0x0` at ten insertion points — all measured flat or worse.

The two open questions are now sharply stated:
1. **What honest construct spends one temp-register web and emits nothing?** Everything obvious
   has been tried. Candidates not yet reachable: a fifth declared local (the frame is full and
   exactly explained, so there is no room — see the frame decode below), or a different
   *type* for `unk14` that makes the mask a two-step operation. Note the requirement is narrow:
   it must not change instruction count (267) or any stack offset.
2. Block 5's group ordering, which is insensitive to everything tried in ~380 variants.

## The frame, re-read under the declaration-list law (unchanged, still fully explained)

```
locals area ends at framesize:  spA0  160..247 (0x58 = 88)   <- declared first
                                sp44   68..159 (0x5C = 92)
                                temp_v0@64  temp_type@60  i@56
base (outgoing args + saved regs + compiler temps) = 52
framesize = roundup8(52 + sum(sizeof(local))) = roundup8(52 + 192) = roundup8(244) = 248
```

Calibrated directly: adding 1 unused scalar keeps 248 (the round-up absorbs it), adding 2 gives
256, 4 gives 264, 8 gives 280, 16 gives 312 — all exactly `roundup8(52 + L)`. **Unreferenced
locals are NOT dropped by IDO**; they occupy their home like any other. So the declaration list
is right, and there is no room for a cached `D_80082FA0` or any other extra local.

## Still true from earlier revisions (do not re-explore)

* `if (arg1)` not `if (arg1 != 0)` — the u8-parameter law, threshold at TWO explicit `!= 0`
  comparisons; worth 1737 and it fixes the instruction count (269 → 267).
* `spA0.unk44 = *(u8*)(arg0+0x23D);` must be **above** the `unk14` mask pair (1944 points).
* the loop-counter init `i = 0;` lifted out of the `for` and placed **immediately ahead of**
  `sp44.unk24 = 0.0f;` (65 points; golden's `move s0,zero` precedes `swc1 $f2,0x68(sp)`).
* `func_1515548C(descriptor*, u8 kind, 0, 0, size, u8, s32)`; caller does
  `memcpy((u8*)ret + 0x70, &payload, size)`. Keep `temp_type` `s32` (call site does
  `andi a1,v0,0xff`).
* `spA0.unk14` is **u16** (golden reloads with `lhu`), not the `s16` the sibling files declare.
* `D_800AAE88..98` are real globals in `asm/data/24F740.rodata.s` — **no rodata migration.**
* **The sibling `func_151CAB78` contains byte-identical text.** Anchor every edit between
  `void func_151CA6A0(` and `void func_151CAACC(`. Every generator used this wave does.

## REFUSED

* `spA0.unk14 |= 0x0;` (172) — **dropped this wave as a forcer**, see above.
* `spA0.unk14 += 0;`, `|= (0 << 1)`, `|= (spA0.unk14 & 0x0)` (all 172) — same construct wearing
  different clothes; recorded only to show the binary cannot tell them apart.
* the permuter's `if ((short) arg1)` (562 at 269 instructions), `(unsigned short)` on a pointer
  NULL test (semantically wrong), and the gratuitous `(long long)` shift-count cast (467).
