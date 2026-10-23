import sys
s=sys.stdin.read(); i=s.index('void func_1502457C(s32 arg0, s32 arg1) {'); a=s.rindex('#ifdef NON_MATCHING\n',0,i)+len('#ifdef NON_MATCHING\n'); b=s.index('\n}\n',i)+3
print(s[a:b])
