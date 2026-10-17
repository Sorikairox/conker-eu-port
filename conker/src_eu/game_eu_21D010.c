#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_10023BC0(void); // __osPiGetAccess
void func_10023C04(void); // __osPiRelAccess

// osPiReadIo
s32 func_151EF800(u32 devAddr, u32 *data) {
    register s32 ret;

    func_10023BC0();
    ret = osPiRawReadIo(devAddr, data);
    func_10023C04();
    return ret;
}
