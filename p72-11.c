#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MaxSize 20

typedef int ElemType;
typedef struct SNode {
	ElemType data;
	struct SNode* next;
} SLinkNode;

void CreateLink(SLinkNode* head, int* data, int amount) {
	SLinkNode* p = head;
	for (int i = 0; i < amount; i++) {
		SLinkNode* s = (SLinkNode*)malloc(sizeof(SLinkNode));
		s->data = data[i];
		s->next = 0;
		p->next = s;
		p = s;
	}
}

void Find_mess(SLinkNode* head, ElemType x) {
	SLinkNode* p = head;
	int count = 0;
	while ((p = p->next) != 0) {
		count++;
		if (p->data == x) {
			printf("\n%d 在第%d个节点\n", x, count);
			return;
		}
	}
	printf("\n没有找到值等于%d的节点\n", x);
	return;
}


int GetLength(SLinkNode* head) {	//不算头节点的长度
	int len = 0;
	SLinkNode* p = head;
	while ((p = p->next) != 0)
		len++;
	return len;
}

void Find_ascending_binary(SLinkNode* head, ElemType x, int len) {
	SLinkNode* p = head;
	if (len == 0) {
		printf("\n没有找到值等于%d的节点\n", x);
		return;
	}
	for (int i = len; i > len / 2; i--) {
		p = p->next;
		if (p == 0) {
			printf("\n没有找到值等于%d的节点\n", x);
			return;
		}
	}
	if (p->data == x) {
		printf("\n%d 在第?个节点\n", x);
		return;
	}
	if (x < p->data) {
		Find_ascending_binary(head, x, len / 2);
	}
	if (x > p->data) {
		Find_ascending_binary(p, x, len - len / 2);
	}
}

void Find_ascending(SLinkNode* head, ElemType x) {
	SLinkNode* p = head;
	int count = 0;
	while ((p = p->next) != 0) {
		count++;
		if (p->data == x) {
			printf("\n%d 在第%d个节点\n", x, count);
			return;
		}
		if (p->data > x) {
			printf("\n没有找到值等于%d的节点\n", x);
			return;
		}
	}
	printf("\n没有找到值等于%d的节点\n", x);
	return;
}

void Find_descending(SLinkNode* head, ElemType x) {
	SLinkNode* p = head;
	int count = 0;
	while ((p = p->next) != 0) {
		count++;
		if (p->data == x) {
			printf("\n%d 在第%d个节点\n", x, count);
			return;
		}
		if (p->data < x) {
			printf("\n没有找到值等于%d的节点\n", x);
			return;
		}
	}
	printf("\n没有找到值等于%d的节点\n", x);
	return;
}

void ShowList(SLinkNode* head) {
	SLinkNode* p = head;
	while ((p = p->next) != 0) {
		printf("%d ", p->data);
//		p = p->next;
	}
}

ElemType data[MaxSize];
void InitData_ascending(ElemType* data) {
	for (int i = 0; i < MaxSize; i++)
		data[i] = 2 * i;
}
void InitData_descending(ElemType* data) {
	for (int i = 0; i < MaxSize; i++)
		data[i] = -2 * i;
}
void InitData_random(ElemType* data) {
	for (int i = 0; i < MaxSize; i++) {
		if (i % 3 == 0)
			data[i] = i;
		else
			data[i] = -i;
	}
}

int main() {
	SLinkNode head;
	int begin, end;
//	InitData_random(data);
//	InitData_descending(data);
	InitData_ascending(data);
	CreateLink(&head, data, MaxSize);
//	printf("\nlength = %d\n", GetLength(&head));
	
	ShowList(&head);
//	begin = clock();
//	Find_mess(&head,5);
//	end = clock();
//	printf("time0 = %d ms\n",end - begin);

//	begin = clock();
//	Find_ascending_binary(&head, -8, 20000000);
//	end = clock();
//	printf("time1 = %d ms\n", end - begin);

//	begin = clock();
//	Find_descending(&head, -5);
//	end = clock();
//	printf("time3 = %d ms\n", end - begin);

	begin = clock();
	Find_ascending(&head, 6);
	end = clock();
	printf("time2 = %d ms\n", end - begin);

	return 0;
}


