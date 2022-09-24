#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#define MaxSize 20

typedef int ElemType;
typedef struct SNode {
    ElemType data;
    struct SNode* next;
} SLinkNode;

void CreateLink(SLinkNode* head, int* data, int amount) {
    SLinkNode* p = head;
    for (int i = 0; i < amount; i++) {
        SLinkNode* s = (SLinkNode*)malloc(sizeof(SLinkNode));
        s->data = data[i];
        s->next = 0;
        p->next = s;
        p = s;
    }
}

void Insert_before_first_biggest(SLinkNode* head,ElemType x){
    SLinkNode* p = head,*s1 = head,*s2 = head,*s3 = head;   //s1:最大  s2:最大前一个  s3:p前一个
    ElemType temp = 0;
    while((p = p->next) != 0){
        if(p->data > temp){
            temp = p->data;
            s1 = p;
            s2 = s3;
        }
        s3 = p;
    }
    if(s1 != head){
        SLinkNode* n = (SLinkNode*)malloc(sizeof(SLinkNode));
        n->data = x;
        s2->next = n;
        n->next = s1;
    }
}

void ShowList(SLinkNode* head) {
    SLinkNode* p = head;
    while ((p = p->next) != 0)
        printf("%d ", p->data);
    putchar('\n');
}

ElemType data[MaxSize];
void InitData_random(ElemType* data) {
    for (int i = 0; i < MaxSize; i++) {
        if (i % 3 == 0)
            data[i] = i;
        else
            data[i] = -i;
    }
}

int main(){
    SLinkNode head;
    InitData_random(data);
    data[10] = 18;
    CreateLink(&head,data,MaxSize);
    Insert_before_first_biggest(&head,666);
    ShowList(&head);
    system("pause");
    return 0; 
}
