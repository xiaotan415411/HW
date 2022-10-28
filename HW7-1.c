#include <malloc.h>
#include <stdio.h>
#include <string.h>
#define MaxSize 100 //非零元素最多个数

typedef double ElemType;
typedef struct {
    int r, c;
    ElemType data;
} MyTriad[MaxSize];
int r, c;

char temp[100], temp_assign1[100];

void assign1(int* r, int* c, short isSoLE) { //输入一行数据。
    short int unsuccess = 1;
    int dot_count = 0;     //在遇到下个空格前只允许出现一次负号和小数点。
    int minus_count = 0;   //其中负号前面不能有数据，后面不能有空格。
    int data_count = 0;    // 如果数据少于列数个，报错，要求重新输入。
    short int data_ed = 0; //遇到数据，便于判断其后空格为间隔符。
    for (int input; unsuccess == 1;) {
        unsuccess = 0;
        data_count = 0;
        minus_count = 0;
        dot_count = 0;
        data_ed = 0;
        for (input = 0;; ++input) {
            temp[input] = getchar();
            if (temp[input] == '\n')
                break; //先输入一串字符
        }
        for (int check = 0; check <= input; check++) { //先扫描一遍
            if ((temp[check] < '0' || temp[check] > '9') && temp[check] != '.' && temp[check] != ' ' && temp[check] != '-' && temp[check] != '\n') {
                printf("输入了多余的字符！请重新输入。\n"); //有非法字符，报错，要求重输。
                if (isSoLE)
                    printf("第%d行：", *r);
                else
                    printf("第%d行：", *r + 1);
                unsuccess = 1;
                break;
            }
            if (temp[check] == '-') {
                minus_count++;
                if (minus_count > 1 || ((temp[check + 1] < '0' || temp[check + 1] > '9') && temp[check + 1] != '.') || (temp[check - 1] != ' ' && check != 0)) {
                    printf("输入不正确！请重新输入。\n");
                    if (isSoLE)
                        printf("第%d行：", *r);
                    else
                        printf("第%d行：", *r + 1);
                    unsuccess = 1;
                    break;
                } else
                    continue;
            }
            if (temp[check] == '.') {
                dot_count++;
                if (dot_count > 1 || temp[check + 1] < '0' || temp[check + 1] > '9') {
                    printf("输入不正确！请重新输入。\n");
                    if (isSoLE)
                        printf("第%d行：", *r);
                    else
                        printf("第%d行：", *r + 1);
                    unsuccess = 1;
                    break;
                } else
                    continue;
            }
            if (temp[check] >= '0' && temp[check] <= '9') {
                data_ed = 1;
            }
            if (temp[check] == ' ') {
                if (data_ed) {
                    data_ed = 0;
                    minus_count = 0;
                    dot_count = 0;
                    data_count++;
                }
                continue;
            }
            if (temp[check] == '\n') {
                if (data_ed)
                    data_count++;
                if (data_count < *c) {
                    printf("输入的元素少于%d个！请重新输入。\n", *c);
                    if (isSoLE)
                        printf("第%d行：", *r);
                    else
                        printf("第%d行：", *r + 1);
                    unsuccess = 1;
                    break;
                }
                break;
            }
        }
        if (unsuccess) {
            memset(temp, 0, 100);
            continue;
        }
        if (data_count < *c) {
            printf("输入的元素少于%d个！请重新输入。\n", *c);
            if (isSoLE)
                printf("第%d行：", *r);
            else
                printf("第%d行：", *r + 1);
            unsuccess = 1;
            memset(temp, 0, 100);
        }
        if (data_count > *c) {
            printf("输入的元素多于%d个！请重新输入。\n", *c);
            if (isSoLE)
                printf("第%d行：", *r);
            else
                printf("第%d行：", *r + 1);
            unsuccess = 1;
            memset(temp, 0, 100);
        }
    }
}

double** CreateMatrix(int r, int c) {
    short isSoLE = 0;
    double** p = (double**)malloc(sizeof(double*) * r); //申请r个一维指针空间
    for (int a = 0; a < r; a++)
        p[a] = (double*)malloc(sizeof(double) * c); //为每个一维数组申请c个int大小的空间
    printf("------------输入一个矩阵------------\n");
    for (int r1 = 0; r1 < r; r1++) {
        printf("第%d行：", r1 + 1);
        assign1(&r1, &c, isSoLE);
        for (int c1 = 0; c1 < c; c1++) {
            short int data_ed = 0;
            for (int indicator = 0; indicator < strlen(temp); indicator++) {
                temp_assign1[indicator] = temp[indicator];

                if (temp[indicator] >= '0' && temp[indicator] <= '9') {
                    data_ed = 1;
                }
                temp[indicator] = ' ';
                if (temp[indicator + 1] == ' ' && data_ed == 1) {
                    data_ed = 0;
                    break;
                }
            }
            p[r1][c1] = strtod(temp_assign1, NULL);
            memset(temp_assign1, 0, 100);
        }
        memset(temp, 0, 100);
    }
    // for (int r1 = 0; r1 < r; r1++) {
    //     for (int c1 = 0; c1 < c; c1++)
    //         printf("%lf\t", p[r1][c1]); //输出处理前矩阵
    //     printf("\n");
    // }
    return p;
}

int Mat2Triad(double** p, MyTriad* list) {
    int count = 0;
    for (int r1 = 0; r1 < r; r1++) {
        for (int c1 = 0; c1 < c; c1++) {
            if (p[r1][c1] != 0) {
                list[count]->r = r1;
                list[count]->c = c1;
                list[count]->data = p[r1][c1];
                count++;
            }
        }
    }
    // putchar('\n');
    for (int i = 0; i < count; i++) {
        printf("%d %d %f\n", list[i]->r, list[i]->c, list[i]->data);
    }
    putchar('\n');
    return count;
}

int MatAdd(MyTriad res[], MyTriad list1[], MyTriad list2[], int count1, int count2) {
    int p = 0, count_res = 0;
    for (int i = 0; i < count1; i++) {
        res[i]->r = list1[i]->r;
        res[i]->c = list1[i]->c;
        res[i]->data = list1[i]->data;
        count_res++;
    }
    for (int i = 0; i < count2; i++) {
        for (int r1 = 0; r1 <= count_res; r1++) {
            if (r1 == count_res) {
                res[r1]->r = list2[i]->r;
                res[r1]->c = list2[i]->c;
                res[r1]->data = list2[i]->data;
                count_res++;
                break;
            }
            if (res[r1]->r == list2[i]->r && res[r1]->c == list2[i]->c) {
                res[r1]->data += list2[i]->data;
                break;
            }
        }
    }
    for (int i = 0; i < count_res; i++) {
        printf("%d %d %f\n", res[i]->r, res[i]->c, res[i]->data);
    }
    putchar('\n');
    return count_res;
}

void Triad2Mat(MyTriad* list, int len) {
    double** k = (double**)malloc(sizeof(double*) * r); //申请r个一维指针空间
    for (int a = 0; a < r; a++)
        k[a] = (double*)malloc(sizeof(double) * c);
    for(int r1 = 0;r1 < r;r1++)
        k[r1][0] = 0;

    for (int i = 0; i < len; i++) {
        k[list[i]->r][list[i]->c] = list[i]->data;;
    }
    for (int r1 = 0; r1 < r; r1++) {
        for (int c1 = 0; c1 < c; c1++)
            printf("%lf\t", k[r1][c1]); //输出处理前矩阵
        printf("\n");
    }
}

int main() {
    MyTriad list1[MaxSize], list2[MaxSize];
    MyTriad res[MaxSize];
    printf("输入行数 列数：");
    scanf("%d%d", &r, &c);
    getchar();
    double** p = CreateMatrix(r, c);
    double** q = CreateMatrix(r, c);
    printf("------------第一个三元组------------\n");
    int count1 = Mat2Triad(p, list1);
    printf("------------第二个三元组------------\n");
    int count2 = Mat2Triad(q, list2);
    printf("------------相加后三元组------------\n");
    int count_res = MatAdd(res, list1, list2, count1, count2);
    printf("------------三元组转矩阵------------\n");
    Triad2Mat(res, count_res);
}
