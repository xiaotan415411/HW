#include <malloc.h>
#include <stdio.h>

typedef char ElemType;
typedef struct node {
    ElemType data;
    struct node* Lchild;
    struct node* Rchild;
} BTNode;

BTNode* CreateBT1(char* pre, char* in, int n) {
    BTNode* s;
    char* p;
    int k;
    if (n <= 0)
        return NULL;
    s = (BTNode*)malloc(sizeof(BTNode));
    s->data = *pre;
    s->Lchild = s->Rchild = 0;
    for (p = in; p < in + n; p++)
        if (*p == *pre)
            break;
    k = p - in;
    s->Lchild = CreateBT1(pre + 1, in, k);
    s->Rchild = CreateBT1(pre + k + 1, p + 1, n - k - 1);
    return s;
}

void PreOrder(BTNode* b,char x) {
    if(b == 0)
        return;
    else if(b->data == x){
        if(b->Lchild != 0)
            printf("结点%c的左孩子为:%c\n",b->data,b->Lchild->data);
        if(b->Rchild != 0)
            printf("结点%c的右孩子为:%c\n",b->data,b->Rchild->data);
        else
            printf("结点%c没有子结点\n",b->data);
        return;
    }else if (b != 0) {
        PreOrder(b->Lchild,x);
        PreOrder(b->Rchild,x);
    }
}

int main() {
    ElemType pre[] = "ABDGCEF", mid[] = "DGBAECF";
    BTNode* b1;
    b1 = CreateBT1(pre, mid, 7);
    PreOrder(b1,'C');
}