/* func_1502F01C near-miss, score 820 (asm-differ, object-level).
 * Paste in place of the GLOBAL_ASM pragma in conker/src/game_58F80.c.
 * Residual: (a) obj[0x6F] lands in a1 instead of v1 -> the two arg
 * moves at the jal swap; (b) the first `if (anim != NULL)` branches to
 * the second test instead of straight to the loop end (target uses
 * beqzl -> loop increment). Forcing (b) from C (nesting the 2nd if, or
 * `if (anim == NULL) continue;`) makes IDO LICM-hoist &over[0] into s8,
 * which evicts gfx from s6 and costs far more (1993/6213).
 */
typedef struct {
    u8  pad_0[0x8];
    u8  eyes[2][3];
} EyeDefs;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} EyeTexture;

extern EyeTexture *D_800C5338[];
extern s32 func_1507E908(void *, s32);

Gfx *func_1502F01C(Gfx *gfx, s32 arg1) {
    struct127 *obj;
    u8 tex[2];
    EyeTexture *tbl;
    u8 *anim;
    s32 id;
    s32 i;
    s32 over[2];

    obj = &D_800CC2D0[arg1];
    id = obj->id;
    anim = NULL;
    for (i = 0; i < 2; i++) {
        if (((u8 *)obj)[0x6C + i] >= 0xA) {
            tex[i] = ((u8 *)obj)[0x6C + i] - 0xA;
        } else {
            tex[i] = ((EyeDefs *)D_800D1C90[id])->eyes[i][((u8 *)obj)[0x6C + i]];
            if (((u8 *)obj)[0x6F] != 0 && anim == NULL) {
                anim = (u8 *)func_1507E908(obj, ((u8 *)obj)[0x6F]);
            }
            if (anim != NULL) {
                over[0] = anim[0];
                over[1] = anim[1];
            }
            if (anim != NULL) {
                if (over[i] != ((EyeDefs *)D_800D1C90[id])->eyes[i][2]) {
                    if (((u8 *)obj)[0x6C + i] == 0) {
                        tex[i] = over[i];
                    }
                } else {
                    tex[i] = over[i];
                }
            }
        }
    }

    tbl = D_800C5338[obj->id];
    if (tbl != NULL) {
        gSPSegment(gfx++, 6, tbl[tex[0]].unk0);
        gSPSegment(gfx++, 7, tbl[tex[1]].unk0);
        gSPSegment(gfx++, 0xA, tbl[((u8 *)obj)[0x68]].unk0);
        gSPSegment(gfx++, 0xB, tbl[((u8 *)obj)[0x69]].unk0);
    }
    return gfx;
}
