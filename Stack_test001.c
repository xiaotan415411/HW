#include<stdio.h>
#include<stdlib.h>
#define MaxSize 50

typedef int Elemtype;
typedef struct{
	Elemtype data[MaxSize];
	int top;
}SeqStack;
typedef struct SNode{
	Elemtype data;
	struct SNode* next;
}LinkStack;

void InitSeqStack(SeqStack* s){
	s->top = -1;
}

void InitLinkStack(LinkStack* s){
	s->next = 0;
}

void Push_Seq(SeqStack* s,Elemtype x){
	if(s->top == MaxSize - 1){
		printf("full!\n");
		return;
	}
	s->top++;
	s->data[s->top] = x;
	printf("pushed.(seq)\n");
	return;
}

void Push_Link(LinkStack* head,Elemtype x){
	LinkStack* s = (LinkStack*)malloc(sizeof(LinkStack));
	s->data = x;
	s->next = head->next;
	head->next = s;
	printf("pushed.(link)\n");
	return;
}

void Pop_Seq(SeqStack* s,Elemtype* e){
	if(s->top == -1){
		printf("empty!\n");
		return;
	}
	*e = s->data[s->top];
	s->top--;
	return;
	printf("popped.(seq)\n");
	return;
}

void Pop_Link(LinkStack* head,Elemtype* e){
	if(head->next == 0){
		printf("empty!\n");
		return;
	}
	LinkStack* p = head->next;
	*e = p->data;
	head->next = p->next;
	free(p);
	printf("popped.(link)\n");
	return;
}

void GetTop_Seq(SeqStack* s,Elemtype* e){
	if(s->top == -1){
		printf("empty!\n");
		return;
	}
	*e = s->data[s->top];
	printf("got.(seq)\n");
	return;
}

void GetTop_Link(LinkStack* head,Elemtype* e){
	if(head->next == 0){
		printf("empty!\n");
		return;
	}
	*e = head->next->data;
	printf("got.(link)\n");
	return;
}

int main(){
	SeqStack s;
	return 0;
}
