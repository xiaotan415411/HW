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

// HList LinkTable(HList* h1,HList* h2){
// 	DList* p = h1->next,*q = h2->next;
// 	while(p != 0){
// 		while(q != 0){
// 			for(int seek = 0;seek < h2->col;seek++){
// 				if(q->data[seek]);
// 			}
// 		}
// 	}
// }

void LinkTable_inbook(HList* h1,HList* h2,HList* h){
	int i,j,k;
	DList* p = h1->next,*q,*s,*r;
	printf("连接字段是：第一个表序号，第二个表序号：");
	scanf_s("%d%d",&i,&j);
	// h = (HList*)malloc(sizeof(HList));
	h->row = 0;
	h->col = h1->col + h2->col;
	h->next = 0;
	while (p != 0)
	{
		q = h2->next;
		while (q != 0)
		{
			if(p->data[i-1] == q->data[j-1]){
				s = (DList*)malloc(sizeof(DList));
				for(k = 0;k < h1->col;k++)
					s->data[k] = p->data[k];
				for(k = 0;k < h2->col;k++)
					s->data[k + h1->col] = q->data[k];
				if(h->next == 0)
					h->next = s;
				else
					r->next = s;
				r = s;
				h->row++;
			}
			q = q->next;
		}
		p = p->next;
	}
	r->next = 0;
}

int main() {
	HList head,test1,test2;
	CreateTable(&head);
	CreateTable(&test1);
	// ShowTable(&head);
	LinkTable_inbook(&head,&test1,&test2);
	ShowTable(&test2);
}
