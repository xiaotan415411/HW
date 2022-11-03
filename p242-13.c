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

int PreOrder(BTNode* b) {
    static int cnt = 0;
    if (b != 0) {
        PreOrder(b->Lchild);
        if ((b->Lchild != 0 && b->Rchild == 0) || (b->Lchild == 0 && b->Rchild != 0))
            cnt++;
        PreOrder(b->Rchild);
    }
    return cnt;
}

int main() {
    ElemType pre[] = "ABDHGCEF", mid[] = "HDGBAECF";
    BTNode* b1;
    b1 = CreateBT1(pre, mid, 8);
    printf("\n通过遍历二叉树，统计只有单分支的节点数\n先序序列：%s\t中序序列：%s\ncount = %d\n\n", pre,mid,PreOrder(b1));
}