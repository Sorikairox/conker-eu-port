// ambient_emitters_sort: quicksort of the emitter records D_800DE148[lo..hi] (14 bytes) by x, or by z when
// D_8008D254 is set; pivot = the last record (Rare's partition loop, literal).
void func_1517BE0C(s32 lo, s32 hi) {
    AmbientEmitterRec tmp;
    s32 i = lo;
    s32 j = hi;
    s32 k;
    s16 pivot;

    if (!(lo < hi)) {
        return;
    }
    for (;;) {
        k = (D_8008D254 != 0) ? 2 : 0;
        pivot = D_800DE148[hi].pos[k];
        while (D_800DE148[i].pos[k] < pivot && i < hi) {
            i++;
        }
        while (pivot < D_800DE148[j].pos[k] && lo < j) {
            j--;
        }
        if (!(i < j)) {
            break;
        }
        tmp = D_800DE148[i];
        D_800DE148[i] = D_800DE148[j];
        D_800DE148[j] = tmp;
        i++;
        j--;
    }
    tmp = D_800DE148[i];
    D_800DE148[i] = D_800DE148[hi];
    D_800DE148[hi] = tmp;
    func_1517BE0C(lo, i - 1);
    func_1517BE0C(i + 1, hi);
}
