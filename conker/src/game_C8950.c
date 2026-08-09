#include <ultra64.h>
#include "functions.h"
#include "variables.h"


struct248 *func_1509B950(struct248 *);
struct249 *func_1509B704(s16 arg0);
s32 func_1509B5AC(s32 arg0, s32 arg1);
void func_1509B810();
s32 func_1509B8FC(s16 arg0);
void func_1509C120(void);
void func_1509C3A0(void);
void func_150ADAF0();


void func_1509B4A0(s32 arg0, s32 arg1) {
    s32 i;

    if(0) {};

    D_8003C8E0 = 0x5000000;
    func_1509C120();
    func_15096970();

    for (i = 0; i < D_800D2F3C; i++) {
        if (func_1509CBD4(D_800D2F40[i])) {
            func_1509B5AC(D_800D2F40[i], arg1);
        }
    }

    func_1509C3A0();
    D_8003C8E0 = 0;
}

u16 *func_1509B570(s32 arg0) {
    struct248 *temp_v0;
    u16 res;

    temp_v0 = func_1509B704(arg0);
    if (temp_v0 != 0) {
        res = temp_v0->unkA;
        return (s32)temp_v0 + (res & 0xFFFF);
    }
    return NULL;
}

s32 func_1509B5AC(s32 arg0, s32 arg1) {
    register struct249 *node;

    node = func_1509B704((s16)arg0);
    if ((arg1 == 0) && (*(u8 *)((arg0 >> 3) + (s32)D_800D2E4C) & (1 << (arg0 & 7)))) {
        return 0;
    }

    if (node == 0) {
        node = (struct249 *)func_1509B8FC((s16)arg0);
        func_1509B810(node);
        if ((*(u8 *)(((s32)(node->unk0 & (s32)0xFFFF03FF) >> 3) + (s32)D_800D2E4C) & (1 << ((s32)(node->unk0 & (s32)0xFFFF03FF) & 7))) == 0) {
            D_8003C8E0 = 0x6000000;
            func_150ADAF0(node, 0);
            D_8003C8E0 = 0;
        }
        if ((arg1 == 0) || (node->unk0 & 0x400)) {
            node->unk0 |= 0x4000;
        }
    } else if (arg1 != 0) {
        if ((node->unk0 & 0x1000) && !(node->unk0 & 0x800)) {
            bzero((u8 *)node + ((struct248 *)node)->unkA, ((struct248 *)node)->unk6);
        }
    }

    return (s32)node;
}

struct249 *func_1509B704(s16 arg0) {
    struct249 *tmp;
    s32 mask = 0xFFFF03FF;
    s32 i;

    tmp = D_800D2F48.unk4;
    for (i = 0; i < D_800D2F48.length; i++) {
        if (arg0 == (tmp->unk0 & mask)) {
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}


typedef struct Node1509 {
    u8 pad0[0x18];
    struct Node1509 *next;
    struct Node1509 *prev;
} Node1509;

extern void func_10004074();

void func_1509B764(Node1509 *arg0) {
    if (D_800D2F48.length == 1) {
        D_800D2F48.unk4 = 0;
        D_800D2F48.unk8 = 0;
    } else {
        if (arg0 == (Node1509 *)D_800D2F48.unk4) {
            D_800D2F48.unk4 = (struct249 *)arg0->next;
            arg0->next->prev = 0;
        } else {
            arg0->prev->next = arg0->next;
        }
        if (arg0 == (Node1509 *)D_800D2F48.unk8) {
            D_800D2F48.unk8 = (s32)arg0->prev;
            arg0->prev->next = 0;
        } else {
            arg0->next->prev = arg0->prev;
        }
    }
    func_10004074();
    D_800D2F48.length--;
}

void func_1509B810(Node1509 *arg0) {
    Node1509 *tail;
    Node1509 *head;
    s32 mask;
    s32 key;
    s32 i;

    mask = 0xFFFF03FF;
    tail = (Node1509 *)D_800D2F48.unk8;
    key = *(u16 *)arg0 & mask;
    if (D_800D2F48.length == 0) {
        D_800D2F48.unk4 = (struct249 *)arg0;
        D_800D2F48.unk8 = (s32)arg0;
        arg0->next = 0;
        arg0->prev = 0;
        D_800D2F48.length += 1;
        return;
    }

    i = 0;
    if ((s32)D_800D2F48.length > 0) {
        do {
            i++;
            if (((*(u16 *)tail & mask) < key)) {
            if (tail == (Node1509 *)D_800D2F48.unk8) {
                    arg0->prev = tail;
                    arg0->next = 0;
                    tail->next = arg0;
                    D_800D2F48.unk8 = (s32)arg0;
                    D_800D2F48.length += 1;
                    return;
                }
                arg0->prev = tail;
                arg0->next = tail->next;
                tail->next->prev = arg0;
                tail->next = arg0;
                D_800D2F48.length += 1;
                return;
            }
            tail = tail->prev;
        } while (i < (s32)D_800D2F48.length);
    }

    head = (Node1509 *)D_800D2F48.unk4;
    D_800D2F48.unk4 = (struct249 *)arg0;
    arg0->prev = 0;
    arg0->next = head;
    head->prev = arg0;
    D_800D2F48.length += 1;
}

s32 func_1509B8FC(s16 arg0) {
    struct248 *temp_v0;
    s16 sp18[2];

    temp_v0 = func_1502B5C8(&sp18, 2, 20, arg0);
    temp_v0->unk0 |= arg0;
    temp_v0->unk2 = D_800BE9F0;
    func_1509B950(temp_v0);
}

struct248 *func_1509B950(struct248 *arg0) {
    struct248 *copy;
    s32 pad;

    pad = 8 - (((s32)arg0 + arg0->unk4) & 7);
    arg0->unkA = arg0->unk4 + pad;
    arg0->unk4 = arg0->unkA + arg0->unk6;
    arg0->unk4 = (arg0->unk4 - (((s32)arg0 + arg0->unk4) & 7)) + 8;

    copy = allocate_memory(arg0->unk4, 0xFF, 2, 0);
    if (copy == NULL) {
        while (1) {}
    }

    bcopy(arg0, copy, arg0->unk4);
    bzero((u8 *)copy + copy->unkA, copy->unk6);
    func_10004074(arg0);
    return copy;
}

extern s32 D_8003C8E0;
extern s32 D_800BE9F0;
extern s32 D_800D2E70;
extern struct102 *D_800D2E4C;
extern struct250 D_800D2F48;
void func_1509C228(void);
void func_150ADAF0();
extern u8 D_800D2E69;
void func_1509B764(Node1509 *arg0);
void func_1509BA04(s32 arg0)
{
  register struct249 *node;
  register struct249 *next;
  s32 count;
  s32 i;
  count = D_800D2F48.length;
  node = D_800D2F48.unk4;
  if (D_800D2E69 != 0)
  {
    func_1509C228();
    D_800D2E69 = 0;
  }
  i = 0;
  if (count > 0)
  {
    u8 *table;
    s32 tmp;
    s32 value;
    table = (u8 *) (&D_800D2E70);
    do
    {
      value = node->unk0;
      tmp = value & 0xFFFF03FF;
      next = node->next;
      if ((*(u8 *)((tmp >> 3) + (s32) D_800D2E4C) & (1 << (tmp & 7))) && (arg0 == 0))
      {
        func_1509B764(node);
        table[tmp] = 3;
      }
      else
        if (((arg0 != 0) || (value & 0x8000)) || ((value & 0x1000) && (D_800BE9F0 != (*((u16 *) (((u8 *) node) + 2))))))
      {
        D_8003C8E0 = 0x6000001;
        func_150ADAF0(node, 3);
        D_8003C8E0 = 0;
        func_1509B764(node);
        if ((*(u8 *)((tmp >> 3) + (s32) D_800D2E4C) & (1 << (tmp & 7))) == 0)
        {
          table[tmp] = 0;
        }
        else
        {
          table[tmp] = 3;
        }
      }
      i++;
      node = next;
    }
    while (i != count);
  }
}

void func_1509C228(void);


#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509BBA0.s")

//
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509BE40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509BFB0.s")

// need a bigger brain
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509C120.s")

void func_1509C228(void) {
    if ((D_800D2E68 & 8) || (D_800D2E4C->unkF & 1)) {
        func_1509BFB0(2, 0x2000, 0x36, 0, 1);
        return;
    }
    func_1509BFB0(2, 0x2000, 0x36, 1, 1);
}

s32 func_1509C2A4(void) {
    s32 temp_v0 = D_800BE9F0;
    if ((temp_v0 == 3) ||
        (temp_v0 == 5) ||
        (temp_v0 == 9) ||
        (temp_v0 == 13) ||
        (temp_v0 == 15) ||
        (temp_v0 == 17) ||
        (temp_v0 == 21) ||
        (temp_v0 == 22) ||
        (temp_v0 == 24) ||
        (temp_v0 == 26) ||
        (temp_v0 == 29) ||
        (temp_v0 == 31) ||
        (temp_v0 == 32) ||
        (temp_v0 == 33) ||
        (temp_v0 == 34) ||
        (temp_v0 == 36) ||
        (temp_v0 == 37) ||
        (temp_v0 == 42) ||
        (temp_v0 == 43) ||
        (temp_v0 == 45) ||
        (temp_v0 == 48) ||
        (temp_v0 == 51) ||
        (temp_v0 == 52) ||
        (temp_v0 == 56) ||
        (temp_v0 == 62) ||
        (temp_v0 == 63) ||
        (D_800D2E44 != 0)
      ) {
        return 0;
    }
    return 1;
}

void func_1509C3A0(void) {
    if ((D_800D2E43 != 0) && (D_800D2E44 == 0) && (func_1509C2A4() != 0)) {
        D_800BE3DF = (s8) D_800BE9F4;
        if (D_800C35C4 == 0) {
            func_15007718(D_8008FDA8);
        }
        D_800D2E43 = 0;
    }
}


s32 func_1509C414(s32 arg0) {
    return ((D_800D2E4C->unk3 & 1) << 0xA) + arg0 + 0x1400;
}
