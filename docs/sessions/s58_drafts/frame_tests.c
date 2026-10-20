typedef struct { int a[30]; } S30;
int r1(void); float r2(void); void h(int, float, void*);
void g(void*, int, int, int, int, int);
void a1(void) { S30 sp; sp.a[0]=1; h(r1(), r2(), &sp.a[5]); g(&sp,3,0xFF,0,0,0); }
void a2(void) { S30 sp; sp.a[0]=1; h(0, r2(), &sp.a[5]); g(&sp,3,0xFF,0,0,0); }
void a3(void) { S30 sp; sp.a[0]=1; g(&sp,3,0xFF,0,0,0); }
void a4(void) { S30 sp; sp.a[0]=1; g(&sp,3,0xFF,0,0,0); h(r1(), r2(), &sp.a[5]);}
void a5(void) { S30 sp; sp.a[0]=1; g(&sp,3,0xFF,0,0,0); h(r1(), r2(), (void*)0);}
typedef struct { int a[30]; } S30;
typedef struct { int a[31]; } S31;
typedef struct { int a[29]; } S29;
int r1(void); float r2(void); void h(int, float, void*);
void g(void*, int, int, int, int, int);
void e1(void) { float t; S30 sp; t = r2(); sp.a[1]=t; sp.a[0]=t; h(r1(), r2(), &sp.a[5]); g(&sp,3,0xFF,0,0,0); }
void e2(void) { float t; S31 sp; t = r2(); sp.a[1]=t; sp.a[0]=t; h(r1(), r2(), &sp.a[5]); g(&sp,3,0xFF,0,0,0); }
void e3(void) { S31 sp; h(r1(), r2(), &sp.a[5]); g(&sp,3,0xFF,0,0,0); }
void e4(void) { S29 sp; h(r1(), r2(), &sp.a[5]); g(&sp,3,0xFF,0,0,0); }
void e5(void) { S30 sp; float t; t = r2(); sp.a[1]=t; sp.a[0]=t; h(r1(), r2(), &sp.a[5]); g(&sp,3,0xFF,0,0,0); }
void e6(void) { float t; S30 sp; t = r2(); sp.a[1]=t; sp.a[0]=t; h(r1(), 0, &sp.a[5]); g(&sp,3,0xFF,0,0,0); }
typedef struct { int a[30]; } S30;
int r1(void); float r2(void); void h(int, float, void*);
void g(void*, int, int, int, int, int);
void f1(void) { float t; int pad; S30 sp; t = r2(); sp.a[1]=t; sp.a[0]=t; h(r1(), r2(), &sp.a[5]); g(&sp,3,0xFF,0,0,0); }
void f2(void) { int pad[2]; S30 sp; h(r1(), r2(), &sp.a[5]); g(&sp,3,0xFF,0,0,0); }
void f3(void) { double pad; S30 sp; h(r1(), r2(), &sp.a[5]); g(&sp,3,0xFF,0,0,0); }
void f4(void) { int pad; S30 sp; h(r1(), r2(), &sp.a[5]); g(&sp,3,0xFF,0,0,0); }
void f5(void) { int pad; S30 sp; h(r1(), 0, &sp.a[5]); g(&sp,3,0xFF,0,0,0); }
void f6(void) { int pad[2]; S30 sp; g(&sp,3,0xFF,0,0,0); }
typedef struct { int a[30]; } S30;
int r1(void); float r2(void); void h(int, float, void*);
void g(void*, int, int, int, int, int);
void k1(void) { int p1; int p2; S30 sp; h(r1(), r2(), &sp.a[5]); g(&sp,3,0xFF,0,0,0); }
void k2(void) { float t; S30 sp; int p2; t = r2(); sp.a[1]=t; sp.a[0]=t; h(r1(), r2(), &sp.a[5]); g(&sp,3,0xFF,0,0,0); }
void k3(void) { float t[2]; S30 sp; t[0] = r2(); sp.a[1]=t[0]; sp.a[0]=t[0]; h(r1(), r2(), &sp.a[5]); g(&sp,3,0xFF,0,0,0); }
void k4(void) { int p1; int p2; S30 sp; g(&sp,3,0xFF,0,0,0); }
void k5(void) { int p1; S30 sp; g(&sp,3,0xFF,0,0,0); }
