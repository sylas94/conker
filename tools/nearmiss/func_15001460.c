/* tools/nearmiss/func_15001460.c -- game_2DF70, 324 instructions, frame 0x138
 *
 * STATUS (2026-10-03, cold wave): mism=89, n=324/324, frame EXACT, structdiff 0 insert/delete,
 * 0 opcode rows -- REGISTER-ONLY residue. Splice this body over the pragma (needs the file-local
 * GfxCmd / XZBounds typedefs and `extern s32 D_800DBE40;` shown below).
 *
 * WHAT IT IS: walks an F3DEX2 display list to ENDDL (0xDF), tracks G_VTX (1) vertex pointers
 * (segment-resolved via D_800D2C28[]), decodes TRI1 (5) / TRI2 (6) / Conker's 0x1X 4-tri command,
 * and appends per-triangle vertex pointers (D_800DBE3C, Face16), XZ bounds (D_800DBE40, 8 B/entry)
 * and Y range (D_800DBE44, YRange); D_800DBE38 = running triangle count. D_800DBE63 set => bounds
 * forced to -0x8000/0x7FFF. The duplicated min/max compare block is REAL (golden runs it twice).
 *
 * RESIDUE: starts in the G_VTX case (golden rows 137-153), then t6-t9 rotate by one to the end.
 * Golden: w0 in a2, num in a0, start index in v0, the (s16) cast through t7/t8 so the loop
 * variable gets no register of its own. Ours: loop var takes a2 for the cast's sll, pushing w0
 * to a3. Making the cast go through temps adds a `move` for num (325 instructions).
 * REFUTED (all >= 89): ~290 decl orderings; every k/m/seg/dedicated var assignment to the five
 * loops; num s32+(s16) cast; first as s16/s32/reused seg/reused type; w0 as a named local
 * (always 328); switch; six loop shapes; operand order; register hints.
 * NEXT LEVER: a u8/s8 start-index local, or num/start in a nested block inside the G_VTX arm;
 * else TU-aware permuter restricted to the G_VTX block. Callers in game_305D0.c declare it
 * locally as (s32) -- reconcile with (GfxCmd *) on integration.
 */
typedef struct GfxCmd {
    u32 w0;
    u32 w1;
} GfxCmd;

typedef struct XZBounds {
    s16 minX;
    s16 minZ;
    s16 maxX;
    s16 maxZ;
} XZBounds;

extern s32 D_800DBE40;

void func_15001460(GfxCmd *arg0) {
    s32 i;
    s32 j;
    s32 k;
    s32 m;
    s32 n;
    s32 count;
    GfxCmd *cmd;
    s32 type;
    u32 addr;
    s16 *vtx[32];
    s32 v;
    s16 tri[4][3];
    s16 min[3];
    s16 max[3];
    s16 num;



    if (arg0 == NULL) {
        return;
    }
    n = D_800DBE38;
    for (i = 0; *(s8 *)&arg0[i] != -0x21; i++) {
        cmd = &arg0[i];
        count = 0;
        type = *(s8 *)cmd;
        if ((type >> 4) == 1) {
            tri[0][0] = (cmd->w1 >> 25) & 0x1F;
            tri[0][1] = (cmd->w1 >> 20) & 0x1F;
            tri[0][2] = (cmd->w1 >> 15) & 0x1F;
            tri[1][0] = (cmd->w1 >> 10) & 0x1F;
            tri[1][1] = (cmd->w1 >> 5) & 0x1F;
            tri[1][2] = cmd->w1 & 0x1F;
            tri[2][0] = (cmd->w0 >> 10) & 0x1F;
            tri[2][1] = (cmd->w0 >> 5) & 0x1F;
            tri[2][2] = cmd->w0 & 0x1F;
            tri[3][0] = (cmd->w0 >> 23) & 0x1F;
            tri[3][1] = (cmd->w0 >> 18) & 0x1F;
            tri[3][2] = ((cmd->w1 >> 30) & 3) | ((cmd->w0 >> 13) & 0x1C);
            count = 4;
        } else if (type == 6) {
            tri[0][0] = (cmd->w0 >> 17) & 0x1F;
            tri[0][1] = (cmd->w0 >> 9) & 0x1F;
            tri[0][2] = (cmd->w0 >> 1) & 0x1F;
            tri[1][0] = (cmd->w1 >> 17) & 0x1F;
            tri[1][1] = (cmd->w1 >> 9) & 0x1F;
            tri[1][2] = (cmd->w1 >> 1) & 0x1F;
            count = 2;
        } else if (type == 1) {
            addr = cmd->w1;
            if ((addr >> 24) & 0xF) {
                addr = (&D_800D2C28)[(addr >> 24) & 0xF] + addr - (D_800D2C68 << 24);
            }
            num = ((s32)cmd->w0 >> 12) & 0xFF;
            type = (((s32)cmd->w0 >> 1) & 0x7F) - num;
            for (v = (s16)type; v < num; v++) {
                vtx[v] = (s16 *)addr;
                addr += 0x10;
            }
        } else if (type == 5) {
            for (m = 0; m < 3; m++) {
                tri[0][m] = ((u8 *)cmd)[m + 1] >> 1;
            }
            count = 1;
        }
        for (j = 0; j < count; j++) {
            if ((u32)vtx[0] > 0x100000) {
                for (k = 0; k < 3; k++) {
                    if (D_800DBE63 == 0) {
                        min[k] = max[k] = vtx[tri[j][0]][k];
                        for (m = 1; m < 3; m++) {
                            
                            if (vtx[tri[j][m]][k] < min[k]) {
                                min[k] = vtx[tri[j][m]][k];
                            } else if (vtx[tri[j][m]][k] > max[k]) {
                                max[k] = vtx[tri[j][m]][k];
                            }
                            if (vtx[tri[j][m]][k] < min[k]) {
                                min[k] = vtx[tri[j][m]][k];
                            } else if (vtx[tri[j][m]][k] > max[k]) {
                                max[k] = vtx[tri[j][m]][k];
                            }
                        }
                    } else {
                        min[k] = -0x8000;
                        max[k] = 0x7FFF;
                    }
                }
            }
            for (k = 0; k < 3; k++) {
                ((Face16 *)D_800DBE3C)[n].pts[k] = (Point16 *)vtx[tri[j][k]];
            }
            ((XZBounds *)D_800DBE40)[n].minX = min[0];
            ((XZBounds *)D_800DBE40)[n].maxX = max[0];
            ((XZBounds *)D_800DBE40)[n].minZ = min[2];
            ((XZBounds *)D_800DBE40)[n].maxZ = max[2];
            ((YRange *)D_800DBE44)[n].min = min[1];
            ((YRange *)D_800DBE44)[n].max = max[1];
            n++;
        }
    }
    D_800DBE38 = n;
}
