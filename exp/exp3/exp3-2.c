#include <stdio.h>
#include <string.h>

char s1[100000];
char* minRemoveToMakeValid(char* s) {
    int len = strlen(s),record[100000],count = -1;
    for (int i = 0; i < len; i++) {
        if (s[i] == '(')
            record[++count] = i; //记录左括号位置
        if (s[i] == ')') {
            if (count == -1)
                s[i] = '#';
            else
                count--;
        }
    }
    while (count != -1) {
        s[record[count--]] = '#'; //干掉所有没被匹配的左括号
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
    printf("%s\n", s1);
}