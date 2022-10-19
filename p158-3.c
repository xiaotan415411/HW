#include<stdio.h>
#define MaxSize 100

double data[MaxSize];
double CalcAvg(double data[],int i){
	double avg = 0;
	if(i == 0)
		return data[0] / MaxSize;
	else{
		avg += CalcAvg(data,i-1);
		return avg + data[i] / MaxSize;
	}
}

int main(){
	for(int i = 0;i < MaxSize;i++)
		data[i] = i + 1;
	printf("the average is %.2f\n",CalcAvg(data,MaxSize));
}
