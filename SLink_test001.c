#include<stdio.h>
#include<stdlib.h>
#define MaxSize 20

typedef int ElemType;
typedef struct SNode {
	ElemType data;
	struct SNode* next;
} SLinkNode;

SLinkNode* InitSLink(){
	SLinkNode* head = (SLinkNode*)malloc(sizeof(SLinkNode));
	return head;
}

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

void ShowList(SLinkNode* head) {
	SLinkNode* p = head;
	while ((p = p->next) != 0)
		printf("%d ", p->data);
	putchar('\n');
}

ElemType data[MaxSize];
void InitData(ElemType* data) {
	for (int i = 0; i < MaxSize; i++)
		data[i] = i;
}

int main() {
	InitData(data);
	SLinkNode* head = InitSLink();
	CreateLink(head,data,MaxSize);
	
}
