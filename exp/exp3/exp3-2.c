#include <malloc.h>
#include <stdio.h>
#include <string.h>

typedef struct SNode {
    int data;
    struct SNode* next;
} LinkStack;

void Push_Link(LinkStack* head, int x) {
    LinkStack* s = (LinkStack*)malloc(sizeof(LinkStack));
    s->data = x;
    s->next = head->next;
    head->next = s;
    return;
}

void Pop_Link(LinkStack* head) {
    LinkStack* p = head->next;
    head->next = p->next;
    free(p);
    return;
}

int isEmpty(LinkStack* head) {
    if (head->next == 0)
        return 0; //空
    return 1;     //非空
}

char s1[100000];
char* minRemoveToMakeValid(char* s) {
    LinkStack *stack = (LinkStack*)malloc(sizeof(LinkStack)), *p = stack;
    stack->next = 0;
    int len = strlen(s),record[100000],count = 0;
    for (int i = 0; i < len; i++) {
        if (s[i] == '(')
            Push_Link(stack, i); //记录左括号位置
        if (s[i] == ')') {
            if (isEmpty(stack) == 1) //栈里还有左括号
                Pop_Link(stack);
            else    //栈里没有左括号
                s[i] = '#';
        }
    }
    while (isEmpty(stack) == 1) {
        p = stack->next;
        s[p->data] = '#'; //干掉所有没被匹配的左括号
        Pop_Link(stack);
    }
    int k = 0;
    for (int i = 0; i < len; i++) {
        if (s[i] != '#') {
            s1[k] = s[i];
            k++;
        }
    }
    s1[k] = '\0';
    return s1;
}

int main() {
    char s[] = "ab(c(de)fg)h)()i(";
    // char s[] = "a)b(c)d";
    // char s[] = "))((";
    // char s[] = "abcde";
    char* s1 = minRemoveToMakeValid(s);
    // for(int i = 0;i < strlen(s1);i++){
    //     printf("%c")
    // }
    printf("%s\n", s1);
}