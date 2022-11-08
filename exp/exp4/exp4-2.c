#include <malloc.h>
#include <stdio.h>
#define MaxSize 20

typedef struct node {
    char data;
    struct node *Lchild, *Rchild;
} BTNode;

BTNode* CreateBTree(BTNode* root, char* pre) {
    BTNode *St[MaxSize], *p;
    int top = -1, k = 0, j = 0;
    char ch;
    root = 0;
    ch = pre[j];
    while (ch != '\0') {
        switch (ch) {
        case '(':
            top++;
            St[top] = p;
            k = 1;
            break;
        case ')':
            top--;
            break;
        case ',':
            k = 2;
            break;
        default:
            p = (BTNode*)malloc(sizeof(BTNode));
            p->data = ch;
            p->Lchild = p->Rchild = 0;
            if (root == 0) {
                root = p;
            } else {
                switch (k) {
                case 1:
                    St[top]->Lchild = p;
                    break;
                case 2:
                    St[top]->Rchild = p;
                    break;
                }
            }
            break;
        }
        j++;
        ch = pre[j];
    }
    return root;
}

void traversePre(BTNode* root) {
    if (root != 0) {
        printf("%c", root->data);
        traversePre(root->Lchild);
        traversePre(root->Rchild);
    }
}

void traverseMid(BTNode* root) {
    if (root != 0) {
        traverseMid(root->Lchild);
        printf("%c", root->data);
        traverseMid(root->Rchild);
    }
}

void Swap(BTNode* root) {
    BTNode* temp;
    if (root == 0)
        return;
    if (root->Lchild == 0 && root->Rchild == 0) {
        return;
    } else {
        Swap(root->Lchild);
        Swap(root->Rchild);
        temp = root->Lchild;
        root->Lchild = root->Rchild;
        root->Rchild = temp;
    }
}

void DestoryTree(BTNode* root){
    if(root != 0){
        DestoryTree(root->Lchild);
        DestoryTree(root->Rchild);
        free(root);
    }
}

int main() {
    BTNode* root;
    char pre[] = "A(B(D(,G)),C(E,F))";
    printf("创建树\n");
    root = CreateBTree(root, pre);

    printf("先序遍历\n");
    traversePre(root);

    printf("\n中序遍历\n");
    traverseMid(root);

    printf("\n交换和先序遍历\n");
    Swap(root);
    traversePre(root);

    printf("\n交换后中序遍历\n");
    traverseMid(root);

    printf("\n销毁树\n");
    DestoryTree(root);
}