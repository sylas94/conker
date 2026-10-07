extern s16 D_80084484;

void func_1503F9F0(s16 arg0, s16 *x, s16 *y) {
    OSContPad *pad = ((OSContPad **)D_800BE728[0])[arg0];
    s16 count;

    count = D_80084484 - 1;
    if (count != 0) {
        D_80084484 = count;
        *x = 0;
        *y = 0;
        return;
    }
    D_80084484 = 5;
    if (pad->stick_x < -20 || pad->stick_x > 20) {
        *x = pad->stick_x;
    } else {
        *x = 0;
    }
    if (pad->stick_y < -20 || pad->stick_y > 20) {
        *y = pad->stick_y;
    } else {
        *y = 0;
    }
    pad->stick_x = 0;
    pad->stick_y = 0;
    *x = (*x < -1) ? -1 : ((*x > 1) ? 1 : *x);
    *y = (*y < -1) ? -1 : ((*y > 1) ? 1 : *y);
}
