#include<stdio.h>
#include<stdlib.h>

typedef struct SNode{
    int data;
    struct SNode* next;
}SLinkNode;

void reverse(SLinkNode* head,int left,int right){
    if(left == right){
        printf("ok.\n");
        return;
    }
    SLinkNode* Left = head,*t,*s,*Lprev,*end;
    for (int i = 1; i < left;)
    {
        Left = Left->next;
        i++;
        if(i == left - 1)
            Lprev = Left;
    }
    t = (SLinkNode*)malloc(sizeof(SLinkNode));
    t->data = Left->data;
    s = t;
    end = t;
    Left = Left->next;
    for(int i = 0;i < right - left;i++){
        t = (SLinkNode*)malloc(sizeof(SLinkNode));
        t->data = Left->data;
        t->next = s;
        s = t;
    }
    if(Left->next == 0)
        end->next = 0;
    else
        end = Left->next;
    Lprev->next = s;
}

void CreateSLink(SLinkNode* head,int* data,int amount){
    SLinkNode* s,*r;
    r = head;
    head->data = data[0];
    for(int i = 1;i < amount;i++){
        s = (SLinkNode*)malloc(sizeof(SLinkNode));
        s->data = data[i];
        r->next = s;
        r = s;
    }
    r->next = 0;
}

void ShowList(SLinkNode* head) {
    SLinkNode* p = head;
    while (p != 0){
         printf("%d ", p->data);
        p = p->next;
    }
    putchar('\n');
}

int main(){
    int data[] = {1,2,3,4,5,6,7,8};
    SLinkNode head;
    CreateSLink(&head,data,8);
    reverse(&head,2,4);
    ShowList(&head);
    return 0;
}