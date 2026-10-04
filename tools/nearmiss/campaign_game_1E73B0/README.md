# game_1E73B0 campaign (2026-10-03) -- block 24F370 SHIPPED (uncommitted at time of writing)

C: func_151BEEE0, func_151BF340, func_151BF81C (owners) + func_151BECB8. func_151BE850 stays
GLOBAL_ASM; its constants D_800AA8B0[3] / D_800AA8DC[1] are named stand-ins in golden position
(delete them and use literals once it matches). func_151BE850 best all-C: 62 words (hill-climb 52),
frame/homes/control flow/regions 1-2 exact; residue after the `(arg3 ? 0x10 : 0) | 0xE` join --
golden allocates the ori before the five hoisted constants {1,2,6,-1,8}. Files here.
NOTE: block 24F050 (earlier functions of this TU) ends a separate original file between
func_151BE824 and func_151BE850 -- migrating it will need a TU split (like game_124920/game_125A50).
