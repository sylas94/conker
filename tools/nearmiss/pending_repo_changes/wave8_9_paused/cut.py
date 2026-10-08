import json,sys,collections
# usage: cut.py WAVE NAGENTS PER  -> writes waveW_X.txt (TU-disjoint between agents), appends to tried.txt
W,NA,PER=sys.argv[1],int(sys.argv[2]),int(sys.argv[3])
rows=json.load(open('small_list.json'))
tried=set(open('tried.txt').read().split())
def hw(fn):
    try: a=int(fn[5:],16)
    except: return False
    return 0x150A5000<=a<0x150AE000
import glob,os
busy=set()
for f in sys.argv[4:]:
    busy|={l.split('	')[1] for l in open(f) if l.strip()}
un=[r for r in rows if r[1] not in tried and not r[3] and not hw(r[1]) and r[2] not in busy]
want=NA*PER
picked=un[:want]
# group by TU, assign greedily to least-loaded agent keeping TU together
byTU=collections.OrderedDict()
for r in picked: byTU.setdefault(r[2],[]).append(r)
# pull in same-TU siblings that are just above the cut (cheap: same context)
agents=[[] for _ in range(NA)]
for tu,rs in byTU.items():
    a=min(range(NA),key=lambda i:len(agents[i]))
    agents[a]+=rs
names="ABCDEFG"
with open('tried.txt','a') as t:
    for i,ag in enumerate(agents):
        ag.sort()
        with open(f'wave{W}_{names[i]}.txt','w') as f:
            for r in ag:
                fl=",".join(x for x in r[4:] if x)
                f.write(f"{r[1]}\t{r[2]}\t{r[0]}B\t{fl}\n"); t.write(r[1]+"\n")
        print(names[i],len(ag),"funcs,",len({r[2] for r in ag}),"TUs, sizes",ag[0][0],"-",ag[-1][0])
