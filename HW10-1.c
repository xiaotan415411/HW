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
        root->Rchild = CreateNode(root->Rchild, data);
        return root;
    } else if (data > root->data) {
        root->Lchild = CreateNode(root->Lchild, data);
        return root;
    }
}

BTNode* CreateBSerachTree(BTNode* root, int* post, int total) {
    for (int i = total; i >= 0; i--)
        root = CreateNode(root, post[i]);
    return root;
}

void traversePost(BTNode* root) {
    if (root != 0) {
        traversePost(root->Lchild);
        traversePost(root->Rchild);
        printf("%d ", root->data);
    }
}

void Swap(int* post, int left, int left_cnt, int right) {
    // 每个数需要循环right-left次完成交换
    if (right < 0)
        return;
    int tmp = 0, move_indicator = 0;
    for (int i = 0; i < left_cnt; i++) {
        move_indicator = left;
        for (int j = 0; j < right - left; j++, move_indicator++) {
            tmp = post[move_indicator + 1];
            post[move_indicator + 1] = post[move_indicator];
            post[move_indicator] = tmp;
        }
        left--;
        right--;
    }
}

int FindTempHeadLoc(int* post, int temp_head) {
    if (temp_head < 0)
        return -1;
    int i = 0;
    while (post[i] != temp_head)
        i++;
    return i;
}

void Divide(int* post, int headLoc) {
    if (headLoc < 0)
        return;
    int left = 0, right = 0, temp_head = 0, left_cnt = 0;
    const int init_head = post[headLoc];
    for (left = headLoc - 1; left >= 0; left--) {
        if (post[left] < post[headLoc]) {
            for (int left_counter = left; left_counter >= 0 && post[left_counter] < init_head; left_cnt++, left_counter--) {
            } // 左子树结点个数计数
            break;
        }
    }
    for (right = headLoc - 1; right >= 0; right--) {
        if (post[right] > post[headLoc]) {
            break;
        }
    }
    if (left == right || right < 0)
        return;
    if (right >= 0)
        temp_head = post[right];
    else
        temp_head = -1;
    Swap(post, left, left_cnt, right);
    Divide(post, FindTempHeadLoc(post, temp_head));
    left = right;
    temp_head = post[left];
    Divide(post, FindTempHeadLoc(post, temp_head));
}

int main() {
    BTNode* root = 0;
    int post[] = {9,8,6,4,10};
    root = CreateBSerachTree(root, post, (sizeof(post) / sizeof(post[0])) - 1); //构建反搜索树
    // traversePost(root);  //检验
    printf("左右根:");
    for (int i = 0; i < (sizeof(post) / sizeof(post[0])); i++) {
        printf("%d ", post[i]);
    }
    putchar('\n');
    printf("右左根:");
    Divide(post, (sizeof(post) / sizeof(post[0])) - 1);
    for (int i = 0; i < (sizeof(post) / sizeof(post[0])); i++) {
        printf("%d ", post[i]);
    }
}