typedef struct MenuState {
    f32 x0;
    f32 x4;
    f32 fade;           /* 0x08: page fade-in, >= 0.5 shows the page, 1.0 = done */
    f32 xC;
    f32 x10;
    f32 x14;
    f32 x18;
    f32 x1C;
    u16 input;          /* 0x20: controller 1's menu input bits of this frame */
    u16 padInput[4];    /* 0x22: menu input bits per controller (1 up, 2 down, 4 left, 8 right, 0x10 accept, 0x20 back, 0x40 / 0x80 C buttons) */
    s8 x2A;
    s8 x2B;
    s8 titlePage;       /* 0x2C: page of the title menu (menu 0) */
    s8 x2D;
    s8 stickX[4];       /* 0x2E: last stick x per controller (0 = released, re-arms the edge) */
    s8 stickY[4];       /* 0x32 */
    s8 repeatX[4];      /* 0x36: auto-repeat counters */
    s8 repeatY[4];      /* 0x3A */
    s8 menu;            /* 0x3E: 0 = title menu, 1 = main menu */
    s8 mainPage;        /* 0x3F: page of the main menu (menu 1) */
    s8 prevMainPage;    /* 0x40 */
    s8 x41;
} MenuState;
