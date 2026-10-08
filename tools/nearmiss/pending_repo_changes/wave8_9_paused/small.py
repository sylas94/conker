import os,re,glob,json
CK="conker"
prag={}
for f in glob.glob(CK+"/src/**/*.c",recursive=True):
    for m in re.finditer(r'GLOBAL_ASM\("(asm/nonmatchings/[^"]+/(\w+)\.s)"\)',open(f,errors="replace").read()):
        prag[m.group(2)]=(m.group(1),os.path.relpath(f,CK+"/src")[:-2])
parks={os.path.basename(f)[:-2] for f in glob.glob("tools/nearmiss/func_*.c")}
BAD=re.compile(r'\*/\s+(dmtc1|dmfc1|dadd|daddu|daddi|daddiu|dsub|dsubu|dsll|dsll32|dsrl|dsrl32|dsra|dsra32|dmult|dmultu|ddiv|ddivu|ld|sd|ldl|ldr|sdl|sdr|lwl|lwr|swl|swr|add|sub|addi|neg|eret|mtc0|mfc0|cache|tlbwi|tlbp|tlbr|sync)\s')
rows=[];skip={"orphan":0,"hw":0,"isa":0}
for fn,(p,tu) in prag.items():
    pp=os.path.join(CK,p)
    if not os.path.exists(pp): skip["orphan"]+=1; continue
    t=open(pp,errors="replace").read()
    if "andwritten" in t: skip["hw"]+=1; continue
    if BAD.search(t): skip["isa"]+=1; continue
    n=4*len(re.findall(r'^\s*/\*',t,re.M))
    rows.append([n,fn,tu,"jtbl" if "jtbl_" in t else "", "parked" if fn in parks else "",
                 "rodata" if re.search(r'%lo\((D_\w+)\)\(\$at\)|lwc1|ldc1',t) else ""])
rows.sort()
json.dump(rows,open(os.path.dirname(__file__)+"/small_list.json","w"))
print(skip, len(rows), "candidates")
from collections import Counter
print("size bands:", Counter((r[0]//100)*100 for r in rows[:300]).most_common(8))
for r in rows[:25]: print(r)
