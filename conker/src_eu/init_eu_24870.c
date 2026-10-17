#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern OSThread *D_8002C130; // __osActiveQueue

OSThread *__osGetActiveQueue(void) {
    return D_8002C130;
}
