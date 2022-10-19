#include <stdio.h>
#include <stdlib.h>
#define MaxSize 10

typedef int ElemType;
typedef struct SNode {
    ElemType data;
    struct SNode* next;
} SLinkNode;

void CreateLink(SLinkNode* head, int* data, int amount) {
    SLinkNode* p = head;
    for (int i = 1; i < amount; i++) {
        SLinkNode* s = (SLinkNode*)malloc(sizeof(SLinkNode));
        s->data = data[i];
        s->next = 0;
        p->next = s;
        p = s;
    }
}

void traverseL(SLinkNode* L) {
    SLinkNode* p = L;
    if (p->next == 0) {
        printf("%d ", p->data);
        return;
    } else {
        printf("%d ", p->data);
        traverseL(p->next);
        return;
    }
}

void traverseR(SLinkNode* L) {
    SLinkNode* p = L;
    if (p->next == 0) {
        printf("%d ", p->data);
        return;
    } else {
        traverseR(p->next);
        printf("%d ", p->data);
        return;
    }
}

ElemType data[MaxSize];
void InitData(ElemType* data) {
    for (int i = 0; i < MaxSize; i++)
        data[i] = i;
}

int main() {
    SLinkNode link;
    InitData(data);
    link.data = data[0];
    CreateLink(&link, data, MaxSize); //创建不带头节点单链表
    traverseL(&link);
    putchar('\n');
    traverseR(&link);
}