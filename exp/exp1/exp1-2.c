#include<stdio.h>
#include<stdlib.h>

typedef struct SNode{
    int data;
    struct SNode* next;
}SLinkNode;

SLinkNode* reverse(SLinkNode* head,int left,int right){
    if(left == right)
        return head;
    SLinkNode* Left = head,*t,*s,*Lprev = head,*end;
    for (int i = 1; i < left;)
    {
        Left = Left->next;
        i++;
        if(left > 2 && i == left - 1)
            Lprev = Left;
    }
    t = (SLinkNode*)malloc(sizeof(SLinkNode));
    t->data = Left->data;
    s = t;
    end = t;
    for(int i = 0;i < right - left;i++){
        t = (SLinkNode*)malloc(sizeof(SLinkNode));
        Left = Left->next;
        t->data = Left->data;
        t->next = s;
        s = t;
    }
        end->next = Left->next;
    if(left == 1)
       return s;
    else{
        Lprev->next = s;
        return head;
    }
}

int GetLength(SLinkNode* head){
    int len = 1;
    SLinkNode* p = head;
    while((p = p->next) != 0)
        len++;
    return len;
}

SLinkNode* CreateSLink(SLinkNode* head,int* data,int amount){
    head = (SLinkNode*)malloc(sizeof(SLinkNode));
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
    return head;
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
    int data[] = {1};
    SLinkNode* head = CreateSLink(head,data,1);
    // printf("%d\n",GetLength(&head));
    head = reverse(head,1,1);
    ShowList(head);
    return 0;
}