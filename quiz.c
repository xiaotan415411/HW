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

void NodeSum(BTNode* root, int* sum) {
    if (root != 0) {
        *sum += root->data;
        NodeSum(root->Lchild, sum);
        NodeSum(root->Rchild, sum);
    }
}

void NodeCount(BTNode* root, int* count) {
    if (root != 0) {
        ++*count;
        NodeCount(root->Lchild, count);
        NodeCount(root->Rchild, count);
    }
}

void PutAllOddBeforeEven(int arr[], int length) {
    int* ans = (int*)malloc(sizeof(int) * length);
    int front, back;
    for (back = 0; back < length; back++) {
        if (arr[back] % 2 == 0) {
            front = back + 1;
            break;
        }
    }
    for (; front < length; front++) {
        if (arr[front] % 2 == 1) {
            int temp = arr[front];
            arr[front] = arr[back];
            arr[back] = temp;
            back++;
        }
    }
    for (int i = 0; i < length; i++)
        printf("%d ", arr[i]);
}

int NodeLevel(BTNode* root, int x, int height) {
    int level = 0;
    if (root == 0) {
        return 0;
    }
    if (root->data == x) {
        return height;
    } else {
        level = NodeLevel(root->Lchild, x, height + 1);
        if (level)
            return level;
        else
            return NodeLevel(root->Rchild, x, height + 1);
    }
}

int main() {
    BTNode* root = 0;
    int post[] = {1, 7, 5, 21, 22, 27, 25, 20, 10};
    root = CreateBSerachTree(root, post, (sizeof(post) / sizeof(post[0])) - 1);

    int sum = 0;
    // NodeSum(root,&sum);
    // printf("%d\n",sum);

    // PutAllOddBeforeEven(post, sizeof(post) / sizeof(post[0]));

    int count = 0;
    // NodeCount(root, &count);
    // printf("%d\n", count);

    printf("%d\n", NodeLevel(root, 21,1));
}