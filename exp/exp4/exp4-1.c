#include <malloc.h>
#include <stdio.h>
#include <string.h>
#define MaxSize 30
#define MaxSonCnt 4

/*
数组R要存结点间的关系
长度一定要大于等于30
    char parent[16];    冒号前为父节点
    char son[16];   冒号后为子节点
*/
typedef struct {
    char parent[16];
    char son[16];
} R;
/*
结点类型
    char data[16];                单位或姓名
    struct SNode* son[MaxSonCnt]; 下属部门或成员
*/
typedef struct SNode {
    char data[16];                // 单位或姓名
    struct SNode* son[MaxSonCnt]; // 下属部门或成员
} SonTreeNode;
typedef struct {
    SonTreeNode* data[MaxSize];
    int front, rear;
} SqQueue;

int Full_or_Empty(SqQueue* queue) {
    if (queue->rear == queue->front)
        return 0; // empty
    else if ((queue->rear + 1) % MaxSize == queue->front)
        return 1; // full
    else
        return 2;
}

SonTreeNode* GetElem(SqQueue* queue) { // 返回队首元素模拟出队
    queue->front = (queue->front + 1) % MaxSize;
    return queue->data[queue->front];
}

void inQueue(SqQueue* queue, SonTreeNode* x) {
    queue->rear = (queue->rear + 1) % MaxSize;
    queue->data[queue->rear] = x;
    // printf("%d got in.\n",x);
}

/*
从文件中读取内容到数组里
*/
void read(R* data) {
    FILE* fp = fopen("abc.txt", "r");
    char temp[35];
    int i;
    for (i = 0; fgets(temp, 100, fp) != 0; i++) {
        for (int j = 0; temp[j] != '\0'; j++) {
            if (temp[j] == ':') {           // 冒号后面的为孩子
                data[i].parent[j++] = '\0'; // 在父母串后加\0
                int k;
                for (k = 0; temp[j] != '\0' && temp[j] != '\n' && temp[j] != ' '; k++, j++) {
                    data[i].son[k] = temp[j];
                }
                data[i].son[k] = '\0'; // 在孩子串后加\0
                break;
            }
            data[i].parent[j] = temp[j]; // 没到冒号都是父母
        }
    }
    for(int a = 0;a < i;a++){
        printf("parent:%-15s\tson:%-15s",data[a].parent,data[a].son);
        putchar('\n');
    }
}

/*
在构造树时判断一个结点是否存在
*/
int isExist(SonTreeNode* NodesAddr[], char* data, int cnt) {
    for (int i = 0; i < cnt; i++) {
        for (int ch = 0; ch < 16; ch++) {
            if (data[ch] == '\0') {
                return i;
            }
            if ((*NodesAddr[i]).data[ch] != data[ch])
                break;
        }
    }
    return -1;
}

/*
令父节点指向子节点
*/
void Point2Son(SonTreeNode* parent, SonTreeNode* son) {
    for (int i = 0; i < MaxSonCnt; i++) {
        if (parent->son[i] == 0) {
            parent->son[i] = son;
            return;
        }
    }
}

/*
根据数组构造树
*/
SonTreeNode* CreateTree(R* data, SonTreeNode* NodesAddr[]) {
    int i = 0, j = 0,
        cnt = 0,    // 节点个数
        fu_loc = 0, // 父节点在地址数组的位置
        zi_loc = 0; // 子节点在地址数组的位置
    for (i = 0; i < MaxSize; i++) {
        if ((fu_loc = isExist(NodesAddr, data[i].parent, cnt)) != -1) { // 存在父节点
            if ((zi_loc = isExist(NodesAddr, data[i].son, cnt)) != -1) {
                Point2Son(NodesAddr[fu_loc], NodesAddr[zi_loc]);               // 存在子节点，父节点指向子节点
            } else {                                                           // 没有子节点
                SonTreeNode* node = (SonTreeNode*)malloc(sizeof(SonTreeNode)); // 创建子节点，并让父节点指向子节点
                NodesAddr[cnt] = node;                                         // 记录这个子节点的地址
                node->son[0] = node->son[1] = node->son[2] = node->son[3] = 0;
                strcpy(node->data, data[i].son);                // 初始化子节点
                Point2Son(NodesAddr[fu_loc], NodesAddr[cnt++]); // 父节点指向子节点
            }
        } else {                                                             // 不存在父节点
            SonTreeNode* parent = (SonTreeNode*)malloc(sizeof(SonTreeNode)); // 创建父节点
            NodesAddr[cnt++] = parent;                                       // 记录这个父节点的地址
            parent->son[0] = parent->son[1] = parent->son[2] = parent->son[3] = 0;
            strcpy(parent->data, data[i].parent); // 初始化父节点

            SonTreeNode* son = (SonTreeNode*)malloc(sizeof(SonTreeNode)); // 创建子节点
            NodesAddr[cnt++] = son;                                       // 记录这个子节点的地址
            son->son[0] = son->son[1] = son->son[2] = son->son[3] = 0;
            strcpy(son->data, data[i].son); // 初始化子节点

            Point2Son(parent, son); // 父节点指向子节点
        }
    }
    return NodesAddr[0];
}

/*
先序遍历输出树
*/
void Traverse(SonTreeNode* root) {
    if (root != 0) {
        printf("%s", root->data);
        int lbrece = 0;
        for (int i = 0; i <= MaxSonCnt; i++) {
            if (i == MaxSonCnt) {
                if (lbrece == 1)
                    printf(")");
                break;
            }
            if (root->son[i] != 0) {
                if (lbrece == 0) {
                    lbrece = 1;
                    printf("(");
                } else
                    printf(",");
                Traverse(root->son[i]);
            }
        }
    }
}

/*
寻找并返回指定结点地址，没有则返回空
*/
int found;
SonTreeNode* Seek(SonTreeNode* root, char* data) {
    found = 0;
    SonTreeNode* p;
    if (root == 0)
        return 0;
    for (int i = 0; i < MaxSonCnt; i++) {
        if (strcmp(root->data, data)) { // not equ
            p = Seek(root->son[i], data);
            if (found)
                return p;
        } else { // equ
            found = 1;
            return root;
        }
    }
}

/*
输出指定结点与其所有祖先
*/
void PrintRelation(SonTreeNode* root, char* data) {
    found = 0;
    if (root == 0)
        return;
    for (int i = 0; i < MaxSonCnt; i++) {
        if (strcmp(root->data, data)) { // not equ
            PrintRelation(root->son[i], data);
            if (found) {
                printf(" 属于 %s", root->data);
                return;
            }
        } else { // equ
            found = 1;
            printf("%s", root->data);
            return;
        }
    }
}

/*
求指定结点下level层结点数
*/
int SonCnt(SonTreeNode* root, char* dept, int level) {
    const SonTreeNode* p = Seek(root, dept);
    // printf("%s",p->data);
    int cnt = 0;
    if (level == 0)
        return 1;
    for (int i = 0; i < MaxSonCnt; i++) {
        if (p->son[i] != 0)
            cnt += SonCnt(p->son[i], p->son[i]->data, level - 1);
    }
    return cnt;
}

/*
求第level层孩子最多的结点
*/
int max = 0;
int MostSon(SonTreeNode* root, int level, SqQueue* most) {
    if (root == 0)
        return 0;
    int temp = 0;
    if (level == 0) {
        return SonCnt(root, root->data, 1);
    }
    for (int i = 0; i < MaxSonCnt; i++) {
        if (root->son[i] != 0) {
            temp = MostSon(root->son[i], level - 1, most);
            if (level == 1) {
                if (temp >= max) {
                    if (temp > max) {
                        while (Full_or_Empty(most) == 1 || Full_or_Empty(most) == 2)
                            GetElem(most);
                        inQueue(most, root->son[i]);
                        max = temp;
                    } else {
                        inQueue(most, root->son[i]);
                        max = temp;
                    }
                }
            }
        }
    }
    return max;
}

int main() {
    printf("(1) 从abc.txt文件读数据到R数组中\n");
    R data[MaxSize];
    read(data);

    printf("\n(2)(3) 由数组R创建树t的孩子链存储结构并输出\n");
    SonTreeNode *addr[MaxSize], *root;
    root = CreateTree(data, addr);
    Traverse(root);

    printf("\n\n(4) 求计算机学院的专业数\n");
    printf("计算机学院有%d个专业。\n", SonCnt(root, "计算机学院", 1));

    printf("\n(5) 求计算机学院的班数\n");
    printf("计算机学院有%d个班\n", SonCnt(root, "计算机学院", 2));

    printf("\n(6) 求电信学院的学生数\n");
    printf("电信学院有%d个学生\n", SonCnt(root, "电信学院", 3));

    printf("\n(7) 求韩愈在哪所学校、哪个学院、哪个专业、哪个班\n");
    PrintRelation(root, "韩愈");

    printf("\n\n(8) 求哪个班级人数最多\n");
    SqQueue* most = (SqQueue*)malloc(sizeof(SqQueue));
    most->front = most->rear = 0;
    printf("最多人数有%d个的班级为", MostSon(root, 3, most));
    while (Full_or_Empty(most) == 1 || Full_or_Empty(most) == 2)
        printf(" %s", GetElem(most)->data);
    return 0;
}
