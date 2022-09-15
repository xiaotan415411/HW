#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MaxSize 20

typedef struct DNode{
	int data;
	struct DNode* prev;
	struct DNode* next;
}DLinkNode;

void CreateDLinkF(DLinkNode*,int*,int);
void CreateDLinkF_inbook(DLinkNode*,int*,int);
void CreateDLinkB(DLinkNode*,int*,int);
void InsertNodeBehind(DLinkNode*,int data,int position);
void DeleteNode(DLinkNode*,int position);
int GetLength(DLinkNode*);
void InsertSortAscending(DLinkNode*);
void ShowList(DLinkNode*);

int data[MaxSize];
int main(){ 
	int begin,end;
	DLinkNode head;
	for(int i = 0;i < MaxSize;i++){
		if(i % 3 == 0)
			data[i] = i;
		else
			data[i] = -i;
	}
	
/****************************创建测试*******************************/
//	begin = clock();
//	CreateDLinkF(&head,data,sizeof(data)/sizeof(data[0]));
//	end = clock();
//	printf("time1 = %d ms\n",end - begin);
//	
//	begin = clock();
//	CreateDLinkF_inbook(&head,data,sizeof(data)/sizeof(data[0]));
//	end = clock();
//	printf("time2 = %d ms",end - begin);


/***************************插入测试**********************************/
//	DLinkNode test1,test2;
//	test1.prev = 0;
//	test1.next = &test2;
//	test2.prev = &test1;
//	test2.next = 0;
//	test2.data = 233;
//	InsertNodeBehind(&test1,999,0);
//	printf("%d",test1.next->data);
	

/****************************尾插法*************************************/
//	DLinkNode head2;
//	CreateDLinkB(&head2,data,MaxSize);
//	ShowList(&head2);


/****************************删除测试***********************************/
//	DLinkNode test3;
//	CreateDLinkF(&test3,data,MaxSize);
//	ShowList(&test3);
//	DeleteNode(&test3,2000);
//	ShowList(&test3);


/****************************计算长度************************************/
//	CreateDLinkF(&head,data,MaxSize);
//	begin = clock();
//	printf("length = %d\n",GetLength(&head));
//	end = clock();
//	printf("time = %d ms\n",end - begin);


/****************************排序测试************************************/
	DLinkNode test4;
//	data[0] = 3;data[1] = 7;data[2] = 5;data[3] = 2;
	CreateDLinkB(&test4,data,MaxSize);
	ShowList(&test4);
	InsertSortAscending(&test4);
	ShowList(&test4);
	
	return 0;
}

void CreateDLinkF(DLinkNode* head,int* data,int amount){
	DLinkNode* newNode;
//	head = (DLinkNode*)malloc(sizeof(DLinkNode));	//为头节点指针申请空间
	head->prev = head->next = NULL;
	
	newNode = (DLinkNode*)malloc(sizeof(DLinkNode));//先创建一个数据节点
	newNode->data = data[0];
	newNode->prev = head;
	newNode->next = 0;
	head->next = newNode;
	for(int i = 1;i < amount;i++){	//不算头节点共 amount 个节点
		newNode = (DLinkNode*)malloc(sizeof(DLinkNode));
		newNode->data = data[i];
		newNode->prev = head;
		newNode->next = head->next;
		head->next->prev = newNode;
		head->next = newNode;
	}
}

void CreateDLinkF_inbook(DLinkNode* L,int* data,int amount){
	DLinkNode* s;
	L->prev = L->next = 0;
	for(int i = 0;i < amount;i++){
		s = (DLinkNode*)malloc(sizeof(DLinkNode));
		s->data = data[i];
		s->next = L->next;
		if(L->next != 0)
			L->next->prev = s;
		L->next = s;
		s->prev = L;
	}
}

void CreateDLinkB(DLinkNode* head,int* data,int amount){
	DLinkNode* p = head,*s;
	for(int i = 0;i < amount;i++){
		s = (DLinkNode*)malloc(sizeof(DLinkNode));
		s->data = data[i];
		s->prev = p;
		s->next = 0;
		p->next = s;
		p = s;
	}
}

void InsertNodeBehind(DLinkNode* link,int data,int position){
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
	printf("insert successfully.\n");
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

void InsertSortAscending(DLinkNode* link){
	DLinkNode* p = link->next->next,*s = link->next,*t = p;
	int len = GetLength(link);
	int ordered = 1;
	while(p != 0){
//		t = t->next;
		for(int i = 1;i <= ordered;i++){	//每个节点从头开始比较大小
			if(p->data < s->data){
				if(t->next == 0){
					p->prev->next = 0;
					p->next = s;
					p->prev = s->prev;
					s->prev->next = p;
					s->prev = p;
					printf("\nSort successfully.\n");
					return;
				}
				s->next = p->next;
				p->next->prev = s;
				p->next = s;
				p->prev = s->prev;
				s->prev = p;
				p->prev->next = p;
			}
			s = s->next;
		}
		if(ordered == len){
			t->next = 0;
			printf("\nSort successfully.\n");
			return;
		}
		ordered++;
		p = t = t->next;
		s = link->next;
	}
	printf("\nSort successfully.\n");
}

void ShowList(DLinkNode* head){
	DLinkNode* p = head->next;
	while(p != 0){
		printf("%d ",p->data);
		p = p->next;
	}
}
