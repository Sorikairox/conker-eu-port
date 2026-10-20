s32 func_1514EF8C(u8 *arg0, s32 arg1, s32 arg2) {
    switch (arg1) {
    case 3:
        if (arg0[0x22] == 2) {
            func_1518E8EC(arg0, 3);
        } else {
            func_1518E8EC(arg0, 2);
        }
        break;
    case 4:
        func_1518E8EC(arg0, 3);
        break;
    case 5:
        func_1518E8EC(arg0, 2);
        break;
    case 6:
        if (arg0[0x22] == 2) {
            func_1518E8EC(arg0, 5);
        } else {
            func_1518E8EC(arg0, 2);
        }
        break;
    case 7:
        func_1518E8EC(arg0, 5);
        break;
    case 8:
        func_1518E8EC(arg0, 2);
        break;
    case 9:
        if (arg0[0x22] == 2) {
            func_1518E8EC(arg0, 6);
        } else {
            func_1518E8EC(arg0, 2);
        }
        break;
    case 10:
        func_1518E8EC(arg0, 6);
        break;
    case 11:
        func_1518E8EC(arg0, 2);
        break;
    case 12:
        func_1518E8EC(arg0, 2);
        break;
    default:
        return func_1514EE0C(arg0, arg1, arg2);
    }
    return 1;
}
