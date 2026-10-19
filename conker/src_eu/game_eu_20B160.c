#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 func_151DD588(s32);
s32 func_151DD6F0(OSMesgQueue *, u8, void *);
s32 func_151DD950(OSMesgQueue *mq, u8 address, void *buffer, s32 nbytes) {
    s32 ret = 0;

    while (func_151DD588(1) != 0) {
    }
    while (nbytes > 0) {
        ret = func_151DD6F0(mq, address, buffer);
        if (ret != 0) {
            return ret;
        }
        nbytes -= 8;
        address++;
        buffer = (u8 *)buffer + 8;
    }
    return ret;
}
