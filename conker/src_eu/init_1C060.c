#include <libaudio.h>
#include "n_libaudio.h"
#include <os_internal.h>
#include <ultraerror.h>

// alUnlink / alLink, expanded inline in this version of the library
#define N_AL_UNLINK(e)                          \
    {                                           \
        ALLink *ln = (ALLink *)(e);             \
                                                \
        if (ln->next != NULL) {                 \
            ln->next->prev = ln->prev;          \
        }                                       \
        if (ln->prev != NULL) {                 \
            ln->prev->next = ln->next;          \
        }                                       \
    }

#define N_AL_LINK(e, after)                     \
    {                                           \
        ALLink *ln = (ALLink *)(e);             \
        ALLink *to = (ALLink *)(after);         \
                                                \
        ln->next = to->next;                    \
        ln->prev = to;                          \
        if (to->next != NULL) {                 \
            to->next->prev = ln;                \
        }                                       \
        to->next = ln;                          \
    }

void n_alEvtqNew(ALEventQueue *evtq, N_ALEventListItem *items, s32 itemCount)
{
    s32 i;
    ALLink *item, *to;

    evtq->eventCount     = 0;
    evtq->allocList.next = 0;
    evtq->allocList.prev = 0;
    evtq->freeList.next  = 0;
    evtq->freeList.prev  = 0;

    for (i = 0; i < itemCount; i++) {
        item = &items[i];
        to = &evtq->freeList;
        // effectively alLink, TODO: macro this?
        item->next = to->next;
        item->prev = to;
        if (to->next) {
            to->next->prev = item;
        }
        to->next = item;
    }

}

ALMicroTime n_alEvtqNextEvent(ALEventQueue *evtq, N_ALEvent *evt) {
    N_ALEventListItem *item;
    ALMicroTime delta;

    item = (N_ALEventListItem *)evtq->allocList.next;
    if (item) {
        N_AL_UNLINK(item);
        bcopy(&item->evt, evt, sizeof(*evt));
        N_AL_LINK(item, &evtq->freeList);
        delta = item->delta;
    } else {
        /* sct 11/28/95 - If we get here, most like we overflowed the event queue */
        /* with non-self-perpetuating events.  Eg. if we filled the evtq with volume */
        /* events, then when the seqp is told to play it will handle all the events */
        /* at once completely emptying out the queue.  At this point this problem */
        /* must be treated as an out of resource error and the evtq should be increased. */
        evt->type = -1;
        delta = 0;
    }
    return delta;
}

void n_alEvtqPostEvent(ALEventQueue *evtq, N_ALEvent *evt, ALMicroTime delta, s32 flags) {
    N_ALEventListItem *item;
    N_ALEventListItem *nextItem;
    ALLink *node;
    s32 postAtEnd = 0;
    OSIntMask mask;

    if (flags & 2) {
        mask = osSetIntMask(OS_IM_NONE);
    }

    item = (N_ALEventListItem *)evtq->freeList.next;
    if (!item) {
        if (flags & 2) {
            osSetIntMask(mask);
        }
        return;
    }

    // keep the last free item unless told otherwise
    if (!item->node.next && !(flags & 1)) {
        if (flags & 2) {
            osSetIntMask(mask);
        }
        return;
    }

    N_AL_UNLINK(item);
    bcopy(evt, &item->evt, sizeof(*evt));

    if (delta == AL_EVTQ_END) {
        postAtEnd = -1;
    }

    for (node = &evtq->allocList; node != 0; node = node->next) {
        if (!node->next) { /* end of the list */
            if (postAtEnd) {
                item->delta = 0;
            } else {
                item->delta = delta;
            }
            N_AL_LINK(item, node);
            break;
        } else {
            nextItem = (N_ALEventListItem *)node->next;

            if (delta < nextItem->delta) {
                item->delta = delta;
                nextItem->delta -= delta;

                N_AL_LINK(item, node);
                break;
            }

            delta -= nextItem->delta;
        }
    }

    if (flags & 2) {
        osSetIntMask(mask);
    }
}

// n_alEvtqFlushType that also returns the time of the first flushed event
/* was func_1001C4F0 */
s32 n_evtq_flush_type_first(ALEventQueue *evtq, s16 type) {
    ALLink *thisNode;
    ALLink *nextNode;
    N_ALEventListItem *thisItem;
    N_ALEventListItem *nextItem;
    OSIntMask mask;
    s32 first = 0;
    s32 time = 0;

    mask = osSetIntMask(OS_IM_NONE);

    thisNode = evtq->allocList.next;
    while (thisNode != 0) {
        nextNode = thisNode->next;
        thisItem = (N_ALEventListItem *)thisNode;
        nextItem = (N_ALEventListItem *)nextNode;
        time += thisItem->delta;
        if (thisItem->evt.type == type) {
            if (first == 0) {
                first = time;
            }
            if (nextItem) {
                nextItem->delta += thisItem->delta;
            }
            N_AL_UNLINK(thisNode);
            N_AL_LINK(thisNode, &evtq->freeList);
        }
        thisNode = nextNode;
    }

    osSetIntMask(mask);
    return first;
}
