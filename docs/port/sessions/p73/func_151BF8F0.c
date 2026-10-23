/* Lives pop-up (called when a life pickup is collected, after sound 0x511): a HUD object (func_15149130, type
 * 0x60, 0x18 bytes of state) holding a sprite (texture 0xA3) and the number of lives left, one or two digit
 * sprites from the glyph table D_800AAC94. Lives = func_150859AC(0, 3) minus the current one, at most 99.
 * D_800D2458 (set by the 4:3 / wide screen code) moves the sprite and the digits. `arg0` / `arg1` are passed
 * through as the last two arguments of every HUD call (0xFF / 1 at the level start). */
s32 func_15157580(void *sprite, s32, s32 alphaBits, s32, s32, s32 depth, s32, s32);
s32 func_151559FC(void *digit, s32, s32, s32, s32, s32, s32);
extern s32 D_800AAC94[10];

typedef struct {
    s32 sprite;     /* func_15157580 handle */
    s32 digit[2];   /* func_151559FC handles (digit[1] stays 0 for one digit) */
    f32 x;
    f32 angle;
    u8 done;
} LivesPopup;       /* the 0x18 bytes copied to the HUD object + 0x28 */

typedef struct {
    u8 u0;          /* 0xC0 */
    s8 u1;
    u8 u2;
    u8 u3;
    u8 u4;
    u8 pad5;
    s16 u6;
    s32 texture;    /* +0x08 */
    s32 uC;
    s32 u10;
    s32 u14;
    s32 u18;
    s32 u1C;
    s32 u20;
    s32 u24;
    s32 u28;
    u8 u2C;
    u8 u2D;
    u8 pad2E[2];
    u8 color[8];    /* +0x30 */
    u8 u38;
    u8 pad39[3];
    s32 u3C;
    u8 u40;
    u8 u41;
    u8 pad42[2];
    f32 x;          /* +0x44 */
    f32 y;
    f32 z;
    u8 pad50[4];
    s16 u54;
    s16 u56;
} LivesSprite;      /* 0x58 bytes, argument of func_15157580 */

typedef struct {
    f32 x;
    f32 y;
    f32 width;
    f32 height;
    u8 glyph;       /* +0x10 */
    u8 pad11;
    s16 u12;
    s16 u14;
    s16 u16;
    s16 u18;
    u8 u1A;
    u8 color[9];    /* +0x1B */
    s32 u24;
    s32 u28;
    s32 u2C;
    s32 u30;
    s32 u34;
    s32 u38;
    s32 u3C;
    u8 u40;
    u8 u41;
    u8 pad42[2];
    u8 u44;
    u8 pad45[3];
    f32 scaleX;     /* +0x48 */
    f32 scaleY;
    f32 u50;
    f32 u54;
} LivesDigit;       /* 0x58 bytes, argument of func_151559FC */

typedef struct {
    f32 pos[3];
    f32 scaleX;
    f32 scaleY;
} LivesSpritePos;   /* copied to the sprite + 0x120 */

void func_151BF8F0(u8 arg0, s32 arg1) {
    LivesSprite spr;
    LivesSpritePos pos;
    LivesDigit dig;
    s32 glyphs[10];
    s32 digits[2];  /* tens, units */
    LivesPopup rec;
    s32 lives;
    s32 i;
    u8 *hud;
    LivesPopup *popup;

    func_151494E0(0, 0x57);
    lives = func_150859AC(0, 3);
    if (lives != 0) {
        lives -= 1;
    }
    if (lives >= 100) {
        lives = 99;
    }
    digits[0] = lives / 10;
    digits[1] = lives % 10;

    rec.sprite = 0;
    bzero(rec.digit, sizeof(rec.digit));
    rec.x = 110.0f;
    rec.angle = sinf(1.9050001f);
    rec.done = 0;
    hud = (u8 *)func_15149130(300, -1, 0x60, -1, 0, 0x49, (struct37 *)sizeof(LivesPopup), arg0, arg1);
    if (hud == NULL) {
        return;
    }
    popup = (LivesPopup *)(hud + 0x28);
    memcpy(popup, &rec, sizeof(LivesPopup));

    /* the sprite */
    spr.texture = 0xA3;
    spr.u0 = 0xC0;
    spr.u1 = -1;
    spr.u2 = 5;
    spr.u3 = 3;
    spr.u6 = 300;
    spr.uC = 8;
    spr.u10 = 0x100000;
    spr.u18 = 0x60601;
    spr.u2D = 8;
    spr.u1C = 1;
    spr.u20 = 0x38;
    spr.u24 = 0x80;
    spr.u28 = 0x20;
    spr.u38 = 0;
    spr.u4 = 0;
    spr.u14 = 0x200004;
    spr.u2C = 0;
    spr.color[0] = 0xFF;
    spr.color[1] = 0xFF;
    spr.color[2] = 0xFF;
    spr.color[3] = 0xFF;
    spr.color[4] = 0xFF;
    spr.color[5] = 0xFF;
    spr.color[6] = 0xFF;
    spr.color[7] = 0xFF;
    spr.u3C = 0;
    spr.u40 = 0;
    spr.u41 = 1;
    spr.u54 = 1;
    spr.u56 = 0xFF;
    spr.x = 300.0f;
    spr.y = (D_800D2458 != 0) ? 32.0f : 79.0f;
    spr.z = 0.0f;
    pos.pos[0] = ((f32 *)D_800A5860)[0];
    pos.pos[1] = ((f32 *)D_800A5860)[1];
    pos.pos[2] = ((f32 *)D_800A5860)[2];
    pos.scaleX = 0.30100003f;
    pos.scaleY = 0.30100003f;
    popup->sprite = func_15157580(&spr, 0, 0x3F800000 /* 1.0f */, 0, 0, 0x14, arg0, arg1);
    if (popup->sprite != 0) {
        memcpy((u8 *)popup->sprite + 0x120, &pos, sizeof(LivesSpritePos));
    }

    /* the digits */
    for (i = 0; i < 10; i++) {
        glyphs[i] = D_800AAC94[i];
    }
    dig.x = -500.0f;
    dig.y = (D_800D2458 != 0) ? -15.0f : -62.0f;
    dig.color[8] = 0xFF;
    dig.u18 = 0xFF;
    dig.u12 = 300;
    dig.u14 = 0x20;
    dig.u16 = 1;
    dig.color[0] = 0xFF;
    dig.color[1] = 0xFF;
    dig.color[2] = 0xFF;
    dig.color[3] = 0xFF;
    dig.u1A = 0;
    dig.color[4] = 0xFF;
    dig.color[5] = 0xFF;
    dig.color[6] = 0xFF;
    dig.color[7] = 0xFF;
    dig.u24 = 0;
    dig.u28 = 0x200004;
    dig.u2C = 0x9F0601;
    dig.u40 = 0;
    dig.u41 = 0;
    dig.u30 = 0x19;
    dig.u34 = 0x13;
    dig.u38 = 0x80;
    dig.u3C = 0x20;
    dig.u44 = 0;
    dig.u50 = 0.0f;
    dig.u54 = 0.0f;
    dig.height = 16.0f;
    dig.width = 16.0f;
    dig.scaleX = 1.0f;
    dig.scaleY = 1.0f;
    if (digits[0] == 0) {
        dig.glyph = glyphs[digits[1]];
        popup->digit[0] = func_151559FC(&dig, 0, 0, 0, 0, arg0, arg1);
        popup->digit[1] = 0;
        return;
    }
    for (i = 0; i < 2; i++) {
        dig.glyph = glyphs[digits[i]];
        popup->digit[i] = func_151559FC(&dig, 0, 0, 0, 0, arg0, arg1);
    }
}
