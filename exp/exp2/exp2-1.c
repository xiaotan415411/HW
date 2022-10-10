#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MaxSize 20

typedef char ElemType;
typedef struct DNode{
	ElemType data;
	struct DNode* prev;
	struct DNode* next;
}DLinkNode;

DLinkNode* InitDLink();
void InsertNodeBehind(DLinkNode*,ElemType data,int position);
ElemType GetNode(DLinkNode*,int);
bool isEmpty(DLinkNode*);
void DeleteNode(DLinkNode*,int position);
void PrintLength(DLinkNode*);
void InsertSortAscending(DLinkNode*);
void ShowList(DLinkNode*);

ElemType data[MaxSize];
int main(){ 
	int begin,end;
	DLinkNode* head = InitDLink();
	InsertNodeBehind(head,'a',0);
	InsertNodeBehind(head,'a',1);
	InsertNodeBehind(head,'a',2);
	InsertNodeBehind(head,'a',3);
	InsertNodeBehind(head,'a',4);
	ShowList(head);
	printf("length is %d\n",GetLength(head));
	printf("%d\n",isEmpty(head));
	printf("%c\n",GetNode(head,3));
	PrintPosition(head,'a');
	return 0;
}

DLinkNode* InitDLink(){
	DLinkNode* s = (DLinkNode*)malloc(sizeof(DLinkNode));
	s->next = 0;
	return s;
}

bool isEmpty(DLinkNode* head){
	if(head->next == 0){
		printf("empty.\n");
		return true;
	}else{
		printf("not empty.\n");
		return false;
	}
}

ElemType GetNode(DLinkNode* head,int position){
	if(position <= 0){
		printf("invalid position!\n");
		return '\0';
	}
	DLinkNode* p = head;
	for(int i = 0;i < position;i++){
		if(p == 0){
			printf("invalid position!\n");
			return '\0';
		}
		p = p->next;
	}
	return p->data;
}

void InsertNodeBehind(DLinkNode* link,ElemType data,int position){
	if(position < 0){
		printf("invalid position!\n");
		return;
	}
	int i = 0;
	DLinkNode* p = link,* s = 0;
	while(i < position){
		i++;
		p = p->next;
	}
	s = (DLinkNode*)malloc(sizeof(DLinkNode));
	s->data = data;
	s->prev = p;
	s->next = p->next;
	if(p->next != 0)
		p->next->prev = s;
	p->next = s;
	printf("insert %c successfully.\n",data);
}

void DeleteNode(DLinkNode* link,int position){
	if(position < 1){
		printf("\ninvalid position!\n");
		return;
	}
	DLinkNode* p = link->next;
	int i = 1;
//	if(position == 0){
//		p->next->prev = 0;
//		free(p);
//		printf("Delete successfully.\n");
//		return;
//	}
	while(i < position){
		i++;
		p = p->next;
		if(p == 0){
			printf("\ninvalid position!\n");
			return;
		}
		if(p->next == 0 && i == position){
			p->prev->next = 0;
			free(p);
			printf("\nDelete node_%d successfully.\n",i);
			return;
		}
	}
	p->prev->next = p->next;
	p->next->prev = p->prev;
	free(p);
	printf("\nDelete node_%d successfully.\n",position);
}

int GetLength(DLinkNode* link){
	int len = 0;
	DLinkNode* p = link;
	while((p = p->next) != 0)
		len++;
	return len;
}

void PrintPosition(DLinkNode* head,ElemType x){
	printf("%c at ",x);
	DLinkNode* p = head;
	int cnt = 0;
	while((p = p->next) != 0){
		cnt++;
		if(p->data == x){
			printf("Node_%d ",cnt);
		}
	}
}

void ShowList(DLinkNode* head){
	DLinkNode* p = head->next;
	while(p != 0){
		printf("%c ",p->data);
		p = p->next;
	}
	putchar('\n');
}
