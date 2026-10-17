#include <ultra64.h>
#include "functions.h"
#include "variables.h"

u32 __osSpGetStatus(void) {
    return IO_READ(SP_STATUS_REG);
}
