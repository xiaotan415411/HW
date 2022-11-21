#include <malloc.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct node {
    int data;
    struct node* Lchild;
    struct node* Rchild;
} BTNode;

int Level(BTNode* root) {
    int ltree = 0, rtree = 0;
    if (root == 0) {
        return 0;
    } else {
        ltree = Level(root->Lchild) + 1;
        rtree = Level(root->Rchild) + 1;
        return ltree > rtree ? ltree : rtree;
    }
}

int NodeCount(BTNode* root, int level) {
    if (root == 0 || level == 0) {
        return 0;
    } else if (level == 1) {
        return 1;
    } else {
        return NodeCount(root->Lchild, level - 1) + NodeCount(root->Rchild, level - 1) + 1;
    }
}

void traverse(BTNode* root, int* flag) {
    if (root == 0) {
        return;
    } else if (root->Rchild != 0 && root->Lchild == 0) {
        *flag = 1;
        return;
    } else {
        traverse(root->Lchild, flag);
        traverse(root->Rchild, flag);
    }
}

// 访问根节点下lev层结点（倒数第二层）
void check(BTNode* root, int lev, int* status) {
    if (*status == -1)
        return;
    if (lev == 0)
        return;
    if (lev == 1) {
        if (*status == 1 && (root->Lchild != 0 || root->Rchild != 0)) {
            *status = -1; // 判定为不是
            return;
        }
        if ((root->Lchild != 0 && root->Rchild == 0) || (root->Lchild == 0 && root->Rchild == 0)) {
            *status = 1; // 临界
            return;
        }
    }
    check(root->Lchild, lev - 1, status);
    check(root->Rchild, lev - 1, status);
}

bool isCompleteTree(BTNode* root) {
    int level = Level(root);
    double complete = 1.0;
    for (int i = 0; i < level - 1; i++)
        complete = 2 * complete;
    complete--;
    if (NodeCount(root, level - 1) != complete)
        return false;
    int flag = 0;
    traverse(root, &flag);
    if (flag)
        return false;
    int status = 0;
    check(root, level - 1, &status);
    if (status == -1)
        return false;
    return true;
}

int main() {
    BTNode* root = 0;
    if (isCompleteTree(root)) // 需要传入一棵树
        printf("yyyyy\n");
    else
        printf("nnnnn\n");
}