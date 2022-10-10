#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MaxSize 5

typedef int ElemType;
typedef struct {
	ElemType data[MaxSize];
	int front,rear;
} SqQueue;

SqQueue* InitRndQueue(){
	SqQueue* q = (SqQueue*)malloc(sizeof(SqQueue));
	q->front = q->rear = 0;
	return q;
}

int Full_or_Empty(SqQueue* queue){
	if(queue->rear == queue->front)
		return 0;	//empty
	else if((queue->rear + 1) % MaxSize == queue->front)
		return 2;	//full
	else return 3;
}

void inQueue(SqQueue* queue,ElemType x){
	if(Full_or_Empty(queue) == 2){
		printf("full!\n");
		return;
	}
	queue->rear = (queue->rear + 1) % MaxSize;
	queue->data[queue->rear] = x;
	printf("%d got in.\n",x);
}

ElemType GetElem(SqQueue* queue){	//取队首元素模拟出队
	if(Full_or_Empty(queue) == 0){
		printf("empty!\n");
		return '\0';
	}
	queue->front = (queue->front + 1) % MaxSize;
	printf("got %d.\n",queue->data[queue->front]);
	return queue->data[queue->front];
}

int Count(SqQueue* queue){
	return (queue->rear - queue->front + MaxSize) % MaxSize;
}

void ShowQueue(SqQueue* queue){
	int count = Count(queue),cur = queue->front;
	for(int i = 0;i < count;i++){
		cur = (cur + 1) % MaxSize;
		printf("%d ",queue->data[cur]);
	}
	putchar('\n');
}

int main() {
	SqQueue* round_queue = InitRndQueue();
	ElemType a;
	inQueue(round_queue,1);
	inQueue(round_queue,2);
	inQueue(round_queue,3);
	inQueue(round_queue,114);
	a = GetElem(round_queue);
	inQueue(round_queue,514);
	a = GetElem(round_queue);
	inQueue(round_queue,1919810);
	a = GetElem(round_queue);
	ShowQueue(round_queue);
}
