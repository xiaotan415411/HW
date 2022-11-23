#include <malloc.h>
#include <stdio.h>

typedef int ElemType;
struct TreeNode {
    ElemType val;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* buildTree(ElemType* preorder, int preorderSize, ElemType* inorder, int inorderSize) {
    struct TreeNode* p;
    if (preorderSize <= 0)
        return 0;
    p = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    p->val = preorder[0];
    p->left = p->right = 0;
    int rootLoc = 0;
    for (rootLoc = 0; rootLoc < preorderSize; rootLoc++) {
        if (inorder[rootLoc] == preorder[0])
            break;
    }
    p->left = buildTree(preorder + 1, rootLoc, inorder, inorderSize);
    p->right = buildTree(preorder + rootLoc + 1, preorderSize - rootLoc - 1, inorder + rootLoc + 1, inorderSize);
    return p;
}

void traversePost(struct TreeNode* root) {
    if (root != 0) {
        traversePost(root->left);
        traversePost(root->right);
        printf("%d ", root->val);
    }
}

int main() {
    int preorder[5] = {3, 9, 20, 15, 7};
    int  inorder[5] = {9, 3, 15, 20, 7};
    // char* preorder = "ABDGCEF",*inorder = "DGBAECF";

    struct TreeNode* root = buildTree(preorder, 5, inorder, 5);
    // traversePost(root);
}