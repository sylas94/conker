#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern void (*D_8008D5C0[])(s32);
extern s32 D_800BE9E4;
void func_1516972C(struct102 *arg0);

/* A bounded FIFO of (data, callbackId) entries with an idle-expiry timer.
 * Nodes are pushed at the tail and released from the head; a released entry is
 * handed to D_8008D5C0[callbackId](data) before its node is freed.
 * TimedQueue/TimedQueueNode below are the same layout as Queue/QueueNode,
 * re-declared locally for func_1518AA10 (the per-frame tick). */
struct TimedQueueNode {
    u8  pad0[0x10];
    s32 data;
    s32 prev;
    struct TimedQueueNode *next;
    u8  callbackId;
};

struct TimedQueue {
    u8  pad0[0x10];
    s32 tail;
    struct TimedQueueNode *head;
    u8  pad18[0x1C - 0x18];
    s32 count;
    u8  pad20[0x22 - 0x20];
    s16 timer;
    u8  flags;
};

void func_1518AA10(struct TimedQueue *arg0) {
    struct TimedQueue *queue;
    struct TimedQueueNode *node;

    queue = arg0;
    if (queue->count != 0) {
        if (queue->timer < 0) {
            node = queue->head;
            if (node->next == 0) {
                queue->tail = 0;
                queue->head = 0;
            } else {
                node->next->prev = 0;
                queue->head = node->next;
            }
            if (node->callbackId != 0) {
                D_8008D5C0[node->callbackId](node->data);
            }
            func_1516972C((struct102 *)node);
            queue->count -= 1;
        } else if (queue->flags & 1) {
            queue->timer -= D_800BE9E4;
        }
    }
}

s32 func_15167A68(s32, s32, s32, s32, s32, s32);

typedef struct QueueNode QueueNode;

typedef struct {
    u8  pad0[0x10];
    QueueNode *tail;
    QueueNode *head;
    s32 maxCount;
    s32 count;
    s16 timerReload;
    s16 timer;
    u8  flags;
} Queue;

Queue *func_1518AADC(s32 maxCount, s16 timerReload, u8 flags) {
    Queue *queue;

    queue = func_15167A68(0x1D, 0, 0x28, 1, 0xFF, 1);
    if (queue == 0) {
        return NULL;
    }
    queue->count = 0;
    queue->maxCount = maxCount;
    queue->timer = timerReload;
    queue->timerReload = timerReload;
    queue->tail = 0;
    queue->head = 0;
    queue->flags = flags;
    return queue;
}

struct QueueNode {
    u8  pad0[0x10];
    s32 data;
    QueueNode *prev;
    QueueNode *next;
    u8  callbackId;
};

QueueNode *func_1518AB60(s32 data, u8 callbackId) {
    QueueNode *node;

    node = func_15167A68(0x1E, 0, 0x20, 1, 0xFF, 1);
    if (node == 0) {
        return NULL;
    }
    node->data = data;
    node->callbackId = callbackId;
    node->prev = 0;
    node->next = 0;
    return node;
}

s32 func_1518ABD0(Queue *arg0, s32 data, u8 callbackId) {
    QueueNode *node;
    Queue *queue;

    queue = arg0;
    if (queue == 0) {
        if (callbackId != 0) {
            D_8008D5C0[callbackId](data);
        }
        return 0;
    }

    node = func_1518AB60(data, callbackId);
    if (node == 0) {
        if (callbackId != 0) {
            D_8008D5C0[callbackId](data);
        }
        return 0;
    }

    node->prev = queue->tail;
    if (node->prev != 0) {
        node->prev->next = node;
    } else {
        queue->head = node;
    }
    queue->tail = node;
    node->next = 0;

    queue->timer = queue->timerReload;
    queue->count += 1;
    if (queue->maxCount < queue->count) {
        node = queue->head;
        queue->count -= 1;
        if (node->next == 0) {
            queue->tail = 0;
            queue->head = 0;
        } else {
            node->next->prev = 0;
            queue->head = node->next;
        }
        if (node->callbackId != 0) {
            D_8008D5C0[node->callbackId](node->data);
        }
        func_1516972C((struct102 *)node);
    }

    return 1;
}
