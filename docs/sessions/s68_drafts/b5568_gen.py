import itertools,sys
HDR='''s32 func_15148310(void *, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, void *, s32, s32, s32);
extern u8 D_8009FFC0[];

typedef struct { s32 x, y, z; } V3i;
'''
STRUCT='''    struct {
        f32 uC0;
        f32 uC4;
        f32 uC8;
        f32 uCC;
        f32 uD0;
        u8 padD4[0x4];
        s8 uD8;
        s8 uD9;
        u8 uDA;
        s8 uDB;
        u8 padDC[0x4];
        V3i uE0;
        s16 uEC;
        s16 uEE;
        u8 padF0[0x5];
        u8 uF5;
        u8 padF6[0xA];
        s32 u100;
        s32 u104;
        s32 u108;
        s32 u10C;
        s32 u110;
        s32 u114;
        s32 u118;
        s8 u11C;
        s8 u11D;
    } sp;
'''
INIT_FIELD='''    sp.uD8 = 8;
    sp.uD9 = 6;
    sp.uDA = s3[0x24];
    sp.uDB = *(s16 *)(s3 + 0x26);
    sp.uEE = 1;
    sp.u100 = 0;
    sp.u104 = 1;
    sp.u108 = 0x160600;
    sp.u10C = 3;
    sp.u110 = 0x10;
    sp.u114 = 0x80;
    sp.u118 = 0x20;
    sp.u11C = 0;
    sp.u11D = 9;
'''
INIT_REF='''    sp.u100 = 0;
    sp.u104 = 1;
    sp.u108 = 0x160600;
    sp.u10C = 3;
    sp.u110 = 0x10;
    sp.u114 = 0x80;
    sp.u118 = 0x20;
    sp.u11C = 0;
    sp.u11D = 9;
    sp.uEE = 1;
    sp.uD9 = 6;
    sp.uD8 = 8;
    sp.uDA = s3[0x24];
    sp.uDB = *(s16 *)(s3 + 0x26);
'''
def body(init, zdecl, locs, u8t):
    t='u8' if u8t else 's32'
    d = locs
    return HDR+'''
void func_150B5568(u8 *arg0) {
'''+(zdecl if zdecl else '')+STRUCT+d.replace('T ',t+' ')+init+'''    sp.uE0 = *(V3i *)(arg0 + 0x10);
    do {
        scale = (func_150ADA68() * ((f32 *)tbl)[2]) + ((f32 *)tbl)[1];
        a = func_150ADA20();
        b = func_150ADA20();
        sa = func_151423D8(a - 0x40);
        ca = func_151423D8(a);
        sb = func_151423D8(b - 0x40);
        r = ((f32 *)tbl)[0];
        rc = r * func_151423D8(b);
        x = ((f32 *)s3)[0] + (rc * sa);
        y = ((f32 *)s3)[1] - (r * sb);
        z = ((f32 *)s3)[2] + (rc * ca);
        sp.uF5 = (func_150ADA20() % (u32) (*(s16 *)(tbl + 0x22) + 1)) + *(s16 *)(tbl + 0x20);
        sp.uEC = (func_150ADA20() % (u32) (*(s16 *)(tbl + 0x1E) + 1)) + *(s16 *)(tbl + 0x1C);
        sp.uC0 = (func_150ADA68() * ((f32 *)tbl)[4]) + ((f32 *)tbl)[3];
        sp.uD0 = (func_150ADA68() * ((f32 *)tbl)[6]) + ((f32 *)tbl)[5];
        sp.uC4 = scale * x;
        sp.uC8 = scale * y;
        sp.uCC = scale * z;
        func_15148310(&sp.uE0, &sp.uC0, 0, 1, 7, 0, 0, 0, 0, 0, 0, &sp.u100, 0, arg0[0xC], arg0[1]);
        ((f32 *)s3)[0x15] -= 1.0f;
    } while (((f32 *)s3)[0x15] > 1.0f);
}
'''
LA='''    f32 scale;
    f32 sa;
    f32 ca;
    f32 sb;
    f32 r;
    f32 rc;
    f32 x;
    f32 y;
    T a;
    T b;
    u8 *tbl;
    u8 *s3;
'''
LB='''    u8 *s3;
    u8 *tbl;
    T a;
    T b;
    f32 scale;
    f32 sa;
    f32 ca;
    f32 sb;
    f32 r;
    f32 rc;
    f32 x;
    f32 y;
'''
PRE='''    s3 = *(u8 **)(arg0 + 0x98);
    tbl = D_8009FFC0 + s3[0x38] * 0x24;
'''
i=0
for init in (INIT_FIELD, INIT_REF):
  for zpos in ('top','after'):
    for L in (LA,LB):
      for u8t in (1,0):
        z='    f32 z;\n'
        src = body(PRE+init, z if zpos=='top' else '', L+(z if zpos=='after' else ''), u8t)
        open(f'v{i}.c','w').write(src); i+=1
print(i)
