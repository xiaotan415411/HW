#include<stdio.h>
#include<stdlib.h>

typedef struct SNode {
	int data;
	struct SNode* next;
} SLinkNode;

SLinkNode* InitSLink() {
	SLinkNode* head = (SLinkNode*)malloc(sizeof(SLinkNode));
	return head;
}

void CreateLink(SLinkNode* head, int* data, int amount) {
	head->data = data[0];
	head->next = 0;
	SLinkNode* p = head;
	for (int i = 1; i < amount; i++) {
		SLinkNode* s = (SLinkNode*)malloc(sizeof(SLinkNode));
		s->data = data[i];
		s->next = 0;
		p->next = s;
		p = s;
	}
}

SLinkNode* DelDub2(SLinkNode* head){
	SLinkNode dum;
	dum.next = head;
	SLinkNode* pre = head,*patch = &dum;
	int temp = 0;
	while(pre != 0){
		temp = pre->data;
		if(pre->next != 0 && pre->next->data != temp){
			patch = pre;
			pre = pre->next;
		}else if(pre->next == 0){
			return dum.next;
		}else{
			pre = pre->next;
			while(pre != 0 && pre->data == temp)
				pre = pre->next;
			patch->next = pre;
		}
	}
	return dum.next;
}

void ShowList(SLinkNode* head) {
	SLinkNode* p = head;
	while (p != 0){
		printf("%d ", p->data);
		p = p->next;
	}
	putchar('\n');
}

#define MaxSize 9
int data[MaxSize];
void InitData(int* data) {
	for (int i = 0; i < MaxSize; i++)
		data[i] = i;
}

int main() {
//	InitData(data);
//	data[7] = 9;
//	data[8] = 9;
//	data[9] = 9;
	int data[] = {1,1,1,2,3,4,5,7,7};
//	int data[] = {1,2,2};
	SLinkNode* head = InitSLink();
	CreateLink(head, data, MaxSize);
//	ShowList(head);
	ShowList(DelDub2(head));
}
