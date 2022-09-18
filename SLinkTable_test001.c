#include<stdio.h>
#include<stdlib.h>
#define MaxCol 10

typedef int ElemType;
typedef struct DNode {
	ElemType data[MaxCol];
	struct DNode* next;
} DList;
typedef struct HNode {
	int row;
	int col;
	DList* next;
} HList;

void CreateTable(HList* head) {
//	head = (HList*)malloc(sizeof(HList));
	printf("input row,col:");
	scanf_s("%d%d", &head->row, &head->col);
	head->next = 0;
	DList* p = head->next, *s;
	for (int i = 0; i < head->row; i++) {
		s = (DList*)malloc(sizeof(DList));
		for (int j = 0; j < head->col; j++)
			scanf_s("%d", &s->data[j]);
		s->next = 0;
		if (head->next == 0)
			head->next = s;
		else
			p->next = s;
		p = s;
	}
	p->next = 0;
	printf("created.\n");
//	for(int i = 0;i < 2;i++)
//		printf("%d ",head->next->data[i]);
}

void ShowTable(HList* head){
	DList* p = head->next;
	while(p != 0){
		for(int i = 0;i < head->col;i++)
			printf("%d ",p->data[i]);
		putchar('\n');
		p = p->next;
	}
}

HList LinkTable(HList* h1,HList* h2){
	DList* p = h1->next,*q = h2->next;
	while(p != 0){
		while(q != 0){
			for(int seek = 0;seek < h2->col;seek++){
				if(q->data[seek]);
			}
		}
	}
}

int main() {
	HList head;
	CreateTable(&head);
	ShowTable(&head);
}
