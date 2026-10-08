#!/usr/bin/env python3
"""Flag banned fake-match constructs on ADDED lines of a candidate TU vs the repo TU.
usage: lint.py <repo_tu.c> <candidate.c>"""
import sys,re,difflib
PAT=[(r'\bif\s*\(\s*0\s*\)',"if (0)"),(r'\bif\s*\(\s*1\s*\)',"if (1)"),
     (r'\b(\w+)\s*&&\s*\1\b',"x && x"),(r'volatile',"volatile"),(r'\bnew_var',"new_var"),
     (r'\bpad\w*\s*\[|\bpad\d*\s*;',"pad local"),(r'\bunused\w*\s*;',"unused local"),
     (r'\bgoto\b',"goto"),(r'^\s*\w+:\s*;?\s*$',"label"),(r'\^\s*0\b',"^ 0"),(r'&\s*0xFFFFFFFF\b',"& 0xFFFFFFFF"),
     (r'\b(arg\d+)\s*=\s*\1\s*;',"param self-assign (ok if unused-param idiom)"),
     (r'\b(\w+)\s*=\s*\1\s*;',"self-assign"),(r'\barg\d+\s*=[^=]',"param overwrite"),
     (r'\*\s*\(\s*volatile',"volatile deref"),(r'\(\s*\w+\s*\+\s*0\s*\)',"+ 0"),(r'\*\s*1\b',"* 1"),
     (r'\{\s*\}',"empty block"),(r'&\s*\w+\s*;\s*$',"addr-of local stmt")]
a=open(sys.argv[1],errors="replace").read().splitlines(); b=open(sys.argv[2],errors="replace").read().splitlines()
hits=0
for l in difflib.unified_diff(a,b,lineterm="",n=0):
    if not l.startswith("+") or l.startswith("+++"): continue
    s=l[1:]
    if s.strip().startswith(("//","/*","*")): continue
    for p,name in PAT:
        if re.search(p,s): print(f"  [{name}] {s.strip()}"); hits+=1
print(f"{hits} flags")
