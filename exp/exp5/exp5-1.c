#include <malloc.h>
#include <stdio.h>
#include <string.h>

typedef struct node {
    char data;
    struct node* Lchild;
    struct node* Rchild;
} BTNode;

BTNode* CreateExpressTeee(char* exp, int front, int rear) {
    BTNode* root = (BTNode*)malloc(sizeof(BTNode));
    if (front == rear) { // 不可再分
        BTNode* p = (BTNode*)malloc(sizeof(BTNode));
        p->data = exp[front];
        p->Lchild = p->Rchild = 0;
        return p;
    }
    int lastOpt = 0, found = 0;
    for (int i = front; i < rear; i++) {
        if (exp[i] == '+' || exp[i] == '-') {
            found = 1;
            lastOpt = i;
        } else if ((exp[i] == '*' || exp[i] == '/') && !found) {
            lastOpt = i;
        }
    }
    root->Lchild = CreateExpressTeee(exp, front, lastOpt - 1); // 构建左子树
    root->Rchild = CreateExpressTeee(exp, lastOpt + 1, rear);  // 构建右子树
    root->data = exp[lastOpt];
    return root;
}

double Calc(BTNode* root) {
    double ans_1 = 0, ans_2 = 0;
    if (root->Lchild == 0 && root->Rchild == 0)
        return root->data - '0';
    ans_1 = Calc(root->Lchild); //遇到叶子时返回，遇到运算符得出结果返回给ans1作为被加数/被减数/被乘数/被除数
    ans_2 = Calc(root->Rchild); //ans2一定是右运算数
    double ans = 0;
    if (root->data == '+')
        ans = ans_1 + ans_2;
    else if (root->data == '-')
        ans = ans_1 - ans_2;
    else if (root->data == '*')
        ans = ans_1 * ans_2;
    else if (root->data == '/') {
        if (ans_2 == 0) {
            printf("cant be divided by 0\n");
            exit(0);
        }
        ans = ans_1 / ans_2;
    }
    return ans;
}

void traverseMid(BTNode* root) {
    if (root != 0) {
        traverseMid(root->Lchild);
        printf("%c ", root->data);
        traverseMid(root->Rchild);
    }
}

int main() {
    char exp[10];
    printf("input exp:");
    scanf("%s", exp);
    BTNode* root = CreateExpressTeee(exp, 0, strlen(exp) - 1);
    traverseMid(root);
    putchar('\n');
    printf("result =  %.2f\n", Calc(root));
}