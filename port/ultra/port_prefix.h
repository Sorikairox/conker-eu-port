/* Force-included (-include) before every game TU in the wasm build. Never seen by IDO.
 *
 * Every libultra entry point that the PC layer (port/ultra/*.c) re-implements is made weak here.
 * Where a game TU still defines its own (decompiled libultra) copy, that copy becomes a weak
 * definition and the strong PC version wins at link time. No game .c file has to change.
 */
#ifndef PORT_PREFIX_H
#define PORT_PREFIX_H

/* threads */
#pragma weak osCreateThread
#pragma weak osStartThread
#pragma weak osStopThread
#pragma weak osDestroyThread
#pragma weak osYieldThread
#pragma weak osSetThreadPri
#pragma weak osGetThreadPri
#pragma weak osGetThreadId
/* messages / events */
#pragma weak osCreateMesgQueue
#pragma weak osSendMesg
#pragma weak osRecvMesg
#pragma weak osJamMesg
#pragma weak osSetEventMesg
/* interrupts, CPU state */
#pragma weak __osDisableInt
#pragma weak __osRestoreInt
#pragma weak __osSetSR
#pragma weak __osGetSR
#pragma weak __osSetFpcCsr
#pragma weak osSetIntMask
#pragma weak __osInitialize_common
/* caches, TLB */
#pragma weak osInvalICache
#pragma weak osInvalDCache
#pragma weak osWritebackDCache
#pragma weak osWritebackDCacheAll
#pragma weak osMapTLB
#pragma weak osUnmapTLB
#pragma weak osUnmapTLBAll
#pragma weak osVirtualToPhysical
/* time */
#pragma weak osGetTime
#pragma weak osGetCount
#pragma weak osSetTimer
/* VI */
#pragma weak osCreateViManager
#pragma weak osViSetMode
#pragma weak osViSetEvent
#pragma weak osViBlack
#pragma weak osViSwapBuffer
#pragma weak osViGetCurrentFramebuffer
#pragma weak osViGetNextFramebuffer
#pragma weak osViSetSpecialFeatures
/* PI (ROM) */
#pragma weak osCreatePiManager
#pragma weak osPiStartDma
#pragma weak osPiRawStartDma
#pragma weak osEPiStartDma
#pragma weak osPiGetStatus
/* SP / DP / AI */
#pragma weak osSpTaskLoad
#pragma weak osSpTaskStartGo
#pragma weak osSpTaskYield
#pragma weak osSpTaskYielded
#pragma weak osDpSetStatus
#pragma weak osAiSetNextBuffer
#pragma weak osAiGetStatus
#pragma weak osAiGetLength
#pragma weak osAiSetFrequency
/* controllers */
#pragma weak osContInit
#pragma weak osContStartReadData
#pragma weak osContGetReadData

#endif
