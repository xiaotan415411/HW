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

char PreOrder(BTNode* b) {
    static char min = 'p';
    if (b != 0) {
        if (b->data < min)
            min = b->data;
        PreOrder(b->Lchild);
        PreOrder(b->Rchild);
    }
    return min;
}

int main() {
    ElemType pre[] = "KBDGCEF", mid[] = "DGBKECF";
    BTNode* b1;
    b1 = CreateBT1(pre, mid, 7);
    printf("\n通过中间变量比较每个节点的数据大小，返回最小值。\n");
    printf("先序序列：%s\t中序序列：%s\ncount = %c\n\n", pre, mid, PreOrder(b1));
}