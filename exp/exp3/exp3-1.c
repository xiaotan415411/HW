#include<stdio.h>
#include<malloc.h>
#define MaxSize 4

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
		return 1;	//full
	else return 2;
}

void inQueue(SqQueue* queue,ElemType x){
	queue->rear = (queue->rear + 1) % MaxSize;
	queue->data[queue->rear] = x;
}

ElemType GetElem(SqQueue* queue){	//返回队首元素模拟出队
	queue->front = (queue->front + 1) % MaxSize;
	return queue->data[queue->front];
}

int Count(SqQueue* queue){
	return (queue->rear - queue->front + MaxSize) % MaxSize;
}

int Check(SqQueue* queue,ElemType x){
    int count = Count(queue),cur = queue->front;
    for(int i = 0;i < count;i++){
        cur = (cur + 1) % MaxSize;
        if(queue->data[cur] == x)
            return 1;
    }
    return 0;
}

void ShowQueue(SqQueue* queue){
	int count = Count(queue),cur = queue->front;
	for(int i = 0;i < count;i++){
		cur = (cur + 1) % MaxSize;
		printf("%d ",queue->data[cur]);
	}
	putchar('\n');
}

int main(){
    SqQueue* round_queue = InitRndQueue();
	ElemType a;
    int i;
    printf("---------功能列表---------\n1.排队  \t2.就诊  \n3.查看队列\t4.不再排队\n5.下班\n\n");
    while(1){
        printf("输入要执行的操作：");
        scanf("%d",&i);
        switch (i)
        {
        case 1:
            if(Full_or_Empty(round_queue) == 1){
                printf("队列已满。\n\n");
                break;
            }
            printf("输入排队病人的病历号：");
            scanf("%d",&a);
            if(Check(round_queue,a) == 1){
                printf("病历号为%d的病人已在队列中。\n\n",a);
                break;
            }
            inQueue(round_queue,a);
            printf("排队成功。\n\n");
            break;
        
        case 2:
            if(Full_or_Empty(round_queue) == 0){
                printf("没有病人正在排队。\n\n");
                break;
            }
            printf("病历号为%d的病人就诊。\n",GetElem(round_queue));
            putchar('\n');
            break;
        
        case 3:
            if(Full_or_Empty(round_queue) == 0){
                printf("没有病人正在排队。\n\n");
                break;
            }
            printf("当前排队情况：\n");
            ShowQueue(round_queue);
            putchar('\n');
            break;
        
        case 4:
            if(Full_or_Empty(round_queue) == 0){
                printf("没有病人正在排队。下班。\n");
                return 0;
            }
            printf("不再排队，余下依次就诊。\n");
            while(Full_or_Empty(round_queue) == 1 || Full_or_Empty(round_queue) == 2)
                printf("病历号为%d的病人就诊。\n",GetElem(round_queue));
            printf("所有病人就诊完毕。下班。\n");
            return 0;
        
        case 5:
            printf("下班。\n");
            return 0;

        default:
            printf("输入有误。请重新输入。\n");
            break;
        }
    }
}