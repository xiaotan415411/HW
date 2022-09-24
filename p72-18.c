#include<stdio.h>
#define MaxSize 10
#include<stdlib.h>

typedef int ElemType;
typedef struct DLNode
{
    ElemType data;
    struct DLNode* prev;
    struct DLNode* next;
}DLinkNode;

void CreateCirDLink(DLinkNode* head,ElemType* data,int amount){
    head->next = head->prev = 0;
    DLinkNode* p = head,*s;
    for(int i = 0;i < amount;i++){
        s = (DLinkNode*)malloc(sizeof(DLinkNode));
        s->data = data[i];
        p->next = s;
        s->prev = p;
        p = s;
        if(i == amount - 1){    //插入到最后一个
            s->next = head;
            head->prev = s;
        }
    }
}

int GetCirDLinkLength(DLinkNode* head){     //不计头节点
    DLinkNode* p = head;
    int length = 0;
    while ((p = p->next) != 0 && p != head)
        length++;
    printf("length is %d\n",length);
    return length;
}

void Insert(DLinkNode* ha,DLinkNode* hb,int i){
    int ha_len = GetCirDLinkLength(ha);
    if(i == 0){
        hb->prev->next = ha->next;
        ha->next->prev = hb->prev;
        hb->prev = ha->prev;
        ha->prev->next = hb;
        printf("inserted.\n");
        return;
    }
    if(i >= ha_len){
        ha->prev->next = hb->next;
        hb->next->prev = ha->prev;
        ha->prev = hb->prev;
        hb->prev->next = ha;
        printf("inserted.\n");
        return;
    }else{
        DLinkNode* p = ha;
        for(int seek = 0;seek < i;seek++)
            p = p->next;
        p->next->prev = hb->prev;
        hb->prev->next = p->next;
        p->next = hb->next;
        hb->next->prev = p;
        printf("inserted.\n");
        return;
    }
}

void ShowCirDLink(DLinkNode* head){
    DLinkNode* p = head;
    while((p = p->next) != 0 && p != head)
        printf("%d ",p->data);
    putchar('\n');
    return;
}

ElemType data[MaxSize];
void InitData(ElemType* data) {
    for (int i = 0; i < MaxSize; i++) {
        if (i % 3 == 0)
            data[i] = i;
        else
            data[i] = i;
    }
}

int main(){
    DLinkNode ha,hb;
    int i = 0;
    InitData(data);
    CreateCirDLink(&ha,data,MaxSize);
    CreateCirDLink(&hb,data,MaxSize);
    ShowCirDLink(&ha);
    printf("input i:");
    scanf("%d",&i);
    Insert(&ha,&hb,i);
    if(i == 0)
        ShowCirDLink(&hb);
    else
        ShowCirDLink(&ha);
    return 0;
}