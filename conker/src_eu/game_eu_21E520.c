#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#include "controller.h"

// libultra contpfs.c; this file is built -O1
s32 __osContRamRead(OSMesgQueue *mq, int channel, u16 address, u8 *buffer);
s32 __osContRamWrite(OSMesgQueue *mq, int channel, u16 address, u8 *buffer, int force);
s32 __osIdCheckSum(u16 *ptr, u16 *csum, u16 *icsum);
s32 __osRepairPackId(OSPfs *pfs, __OSPackId *badid, __OSPackId *newid);
s32 __osCheckPackId(OSPfs *pfs, __OSPackId *temp);
s32 __osPfsSelectBank(OSPfs *pfs);

u16 func_151F0D10(u8 *ptr, int length) {
    int i;
    u32 sum;
    u8 *tmp;

    sum = 0;
    tmp = ptr;
    for (i = 0; i < length; i++) {
        sum += *tmp++;
        sum = sum & 0xFFFF;
    }
    return sum;
}

s32 func_151F0D6C(u16 *ptr, u16 *csum, u16 *icsum) {
    u16 data;
    u32 j;

    data = 0;
    *csum = *icsum = 0;
    for (j = 0; j < 28; j += 2) {
        data = *(u16 *)((u8 *)ptr + j);
        *csum += data;
        *icsum += ~data;
    }
    return 0;
}

s32 func_151F0DD4(OSPfs *pfs, __OSPackId *badid, __OSPackId *newid) {
    s32 ret;
    u8 temp[BLOCKSIZE];
    u8 comp[BLOCKSIZE];
    u8 mask;
    int i;
    int j;
    u16 index[4];

    ret = 0;
    mask = 0;
    if (pfs->activebank != 0) {
        pfs->activebank = 0;
        ERRCK(__osPfsSelectBank(pfs));
    }
    newid->repaired = -1;
    newid->random = osGetCount();
    newid->serial_mid = badid->serial_mid;
    newid->serial_low = badid->serial_low;
    j = 0;
    do {
        pfs->activebank = j;
        ERRCK(__osPfsSelectBank(pfs));
        ERRCK(__osContRamRead(pfs->queue, pfs->channel, 0, temp));
        temp[0] = j | 0x80;
        for (i = 1; i < BLOCKSIZE; i++) {
            temp[i] = ~temp[i];
        }
        ERRCK(__osContRamWrite(pfs->queue, pfs->channel, 0, temp, FALSE));
        ERRCK(__osContRamRead(pfs->queue, pfs->channel, 0, comp));
        for (i = 0; i < BLOCKSIZE; i++) {
            if (comp[i] != temp[i]) {
                break;
            }
        }
        if (i != BLOCKSIZE) {
            break;
        }
        if (j > 0) {
            pfs->activebank = 0;
            ERRCK(__osPfsSelectBank(pfs));
            ERRCK(__osContRamRead(pfs->queue, pfs->channel, 0, temp));
            if (temp[0] != 0x80) {
                break;
            }
        }
        j++;
    } while (j < PFS_MAX_BANKS);
    pfs->activebank = 0;
    ERRCK(__osPfsSelectBank(pfs));
    if (j > 0) {
        mask = 1;
    } else {
        mask = 0;
    }
    newid->deviceid = (badid->deviceid & 0xFFFE) | mask;
    newid->banks = j;
    newid->version = badid->version;
    __osIdCheckSum((u16 *)newid, &newid->checksum, &newid->inverted_checksum);
    index[0] = 1;
    index[1] = 3;
    index[2] = 4;
    index[3] = 6;
    for (i = 0; i < ARRLEN(index); i++) {
        ERRCK(__osContRamWrite(pfs->queue, pfs->channel, index[i], (u8 *)newid, TRUE));
    }
    ERRCK(__osContRamRead(pfs->queue, pfs->channel, 1, temp));
    for (i = 0; i < BLOCKSIZE; i++) {
        if (temp[i] != ((u8 *)newid)[i]) {
            return PFS_ERR_ID_FATAL;
        }
    }
    return 0;
}

s32 func_151F11EC(OSPfs *pfs, __OSPackId *temp) {
    u16 index[4];
    s32 ret = 0;
    u16 sum;
    u16 isum;
    int i;
    int j;

    if (pfs->activebank != 0) {
        pfs->activebank = 0;
        ERRCK(__osPfsSelectBank(pfs));
    }
    index[0] = 1;
    index[1] = 3;
    index[2] = 4;
    index[3] = 6;
    for (i = 1; i < ARRLEN(index); i++) {
        ERRCK(__osContRamRead(pfs->queue, pfs->channel, index[i], (u8 *)temp));
        __osIdCheckSum((u16 *)temp, &sum, &isum);
        if ((temp->checksum == sum) && (temp->inverted_checksum == isum)) {
            break;
        }
    }
    if (i == ARRLEN(index)) {
        return PFS_ERR_ID_FATAL;
    }
    for (j = 0; j < ARRLEN(index); j++) {
        if (j != i) {
            ERRCK(__osContRamWrite(pfs->queue, pfs->channel, index[j], (u8 *)temp, TRUE));
        }
    }
    return 0;
}

s32 func_151F1384(OSPfs *pfs) {
    int k;
    u16 sum;
    u16 isum;
    u8 temp[BLOCKSIZE];
    __OSPackId newid;
    s32 ret;
    __OSPackId *id;

    if (pfs->activebank != 0) {
        pfs->activebank = 0;
        ERRCK(__osPfsSelectBank(pfs));
    }
    ERRCK(__osContRamRead(pfs->queue, pfs->channel, 1, temp));
    __osIdCheckSum((u16 *)temp, &sum, &isum);
    id = (__OSPackId *)temp;
    if ((id->checksum != sum) || (id->inverted_checksum != isum)) {
        ret = __osCheckPackId(pfs, id);
        if (ret == PFS_ERR_ID_FATAL) {
            ERRCK(__osRepairPackId(pfs, id, &newid));
            id = &newid;
        } else if (ret != 0) {
            return ret;
        }
    }
    if ((id->deviceid & 0x01) == 0) {
        ERRCK(__osRepairPackId(pfs, id, &newid));
        id = &newid;
        if ((id->deviceid & 0x01) == 0) {
            return PFS_ERR_DEVICE;
        }
    }
    for (k = 0; k < ARRLEN(pfs->id); k++) {
        pfs->id[k] = ((u8 *)id)[k];
    }
    pfs->version = id->version;
    pfs->banks = id->banks;
    pfs->inode_start_page = 1 + 2 + (2 * pfs->banks);
    pfs->dir_size = 2 * PFS_ONE_PAGE;
    pfs->inode_table = 1 * PFS_ONE_PAGE;
    pfs->minode_table = (1 + pfs->banks) * PFS_ONE_PAGE;
    pfs->dir_table = pfs->minode_table + (pfs->banks * PFS_ONE_PAGE);
    ERRCK(__osContRamRead(pfs->queue, pfs->channel, 7, pfs->label));
    return 0;
}

s32 func_151F15E0(OSPfs *pfs) {
    int k;
    u8 temp[BLOCKSIZE];
    s32 ret;

    if (pfs->activebank != 0) {
        pfs->activebank = 0;
        ERRCK(__osPfsSelectBank(pfs));
    }
    ret = __osContRamRead(pfs->queue, pfs->channel, 1, temp);
    if (ret != 0) {
        if (ret != PFS_ERR_NEW_PACK) {
            return ret;
        }
        ERRCK(__osContRamRead(pfs->queue, pfs->channel, 1, temp));
    }
    for (k = 0; k < ARRLEN(temp); k++) {
        if (pfs->id[k] != temp[k]) {
            return PFS_ERR_NEW_PACK;
        }
    }
    return 0;
}

s32 func_151F16DC(OSPfs *pfs, __OSInode *inode, u8 flag, u8 bank) {
    u8 sum;
    int j;
    s32 ret;
    int offset;
    u8 *addr;

    if (pfs->activebank != 0) {
        pfs->activebank = 0;
        ERRCK(__osPfsSelectBank(pfs));
    }
    if (bank > 0) {
        offset = 1;
    } else {
        offset = pfs->inode_start_page;
    }
    if (flag == PFS_WRITE) {
        inode->inode_page[0].inode_t.page = __osSumcalc((u8 *)&inode->inode_page[offset], (128 - offset) * 2);
    }
    for (j = 0; j < PFS_ONE_PAGE; j++) {
        addr = ((u8 *)inode->inode_page + j * BLOCKSIZE);
        if (flag == PFS_WRITE) {
            ret = __osContRamWrite(pfs->queue, pfs->channel, pfs->inode_table + bank * PFS_ONE_PAGE + j, addr, FALSE);
            ret = __osContRamWrite(pfs->queue, pfs->channel, pfs->minode_table + bank * PFS_ONE_PAGE + j, addr, FALSE);
        } else {
            ret = __osContRamRead(pfs->queue, pfs->channel, pfs->inode_table + bank * PFS_ONE_PAGE + j, addr);
        }
        if (ret != 0) {
            return ret;
        }
    }
    if (flag == PFS_READ) {
        sum = __osSumcalc((u8 *)&inode->inode_page[offset], (128 - offset) * 2);
        if (sum != inode->inode_page[0].inode_t.page) {
            for (j = 0; j < PFS_ONE_PAGE; j++) {
                addr = ((u8 *)inode->inode_page + j * BLOCKSIZE);
                ret = __osContRamRead(pfs->queue, pfs->channel, pfs->minode_table + bank * PFS_ONE_PAGE + j, addr);
            }
            if (sum != inode->inode_page[0].inode_t.page) {
                return PFS_ERR_INCONSISTENT;
            }
            for (j = 0; j < PFS_ONE_PAGE; j++) {
                addr = ((u8 *)inode->inode_page + j * BLOCKSIZE);
                ret = __osContRamWrite(pfs->queue, pfs->channel, pfs->inode_table + bank * PFS_ONE_PAGE + j, addr, FALSE);
            }
        } else {
            for (j = 0; j < PFS_ONE_PAGE; j++) {
                addr = ((u8 *)inode->inode_page + j * BLOCKSIZE);
                ret = __osContRamWrite(pfs->queue, pfs->channel, pfs->minode_table + bank * PFS_ONE_PAGE + j, addr, FALSE);
            }
        }
    }
    return 0;
}

s32 func_151F19FC(OSPfs *pfs) {
    u8 temp[BLOCKSIZE];
    int i;
    s32 ret = 0;

    for (i = 0; i < BLOCKSIZE; i++) {
        temp[i] = pfs->activebank;
    }
    ret = __osContRamWrite(pfs->queue, pfs->channel, 0x400 / BLOCKSIZE * BLOCKSIZE, temp, FALSE);
    return ret;
}
