#include <malloc.h>
#include <stdio.h>

typedef struct node {
    int data;
    struct node* Lchild;
    struct node* Rchild;
} BTNode;

BTNode* CreateNode(BTNode* root, int data) {
    if (root == 0) {
        root = (BTNode*)malloc(sizeof(BTNode));
        root->data = data;
        root->Lchild = root->Rchild = 0;
        return root;
    } else if (data < root->data) {
        root->Lchild = CreateNode(root->Lchild, data);
        return root;
    } else if (data > root->data) {
        root->Rchild = CreateNode(root->Rchild, data);
        return root;
    }
}

BTNode* CreateBSerachTree(BTNode* root, int* post, int total) {
    for (int i = total; i >= 0; i--) 
        root = CreateNode(root, post[i]);
    return root;
}

void traversePre(BTNode* root) {
    if (root != 0) {
        printf("%d ", root->data);
        traversePre(root->Lchild);
        traversePre(root->Rchild);
    }
}

void traverseMid(BTNode* root) {
    if (root != 0) {
        traverseMid(root->Lchild);
        printf("%d ", root->data);
        traverseMid(root->Rchild);
    }
}

int main() {
    BTNode* root = 0;
    int post[] = {1, 7, 5, 21, 22, 27, 25, 20, 10};
    root = CreateBSerachTree(root, post, (sizeof(post) / sizeof(post[0])) - 1);
    traversePre(root);
    putchar('\n');
    traverseMid(root);
}