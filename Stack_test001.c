#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MaxSize 50

typedef char Elemtype;
typedef struct {
	Elemtype data[MaxSize];
	int top;
} SeqStack;
typedef struct SNode {
	Elemtype data;
	struct SNode* next;
} LinkStack;

void InitSeqStack(SeqStack* s) {
	s->top = -1;
}

void InitLinkStack(LinkStack* s) {
	s->next = 0;
}

void Push_Seq(SeqStack* s, Elemtype x) {
	if (s->top == MaxSize - 1) {
		printf("full!\n");
		return;
	}
	s->top++;
	s->data[s->top] = x;
	printf("pushed.(seq)\n");
	return;
}

void Push_Link(LinkStack* head, Elemtype x) {
	LinkStack* s = (LinkStack*)malloc(sizeof(LinkStack));
	s->data = x;
	s->next = head->next;
	head->next = s;
	printf("pushed.(link)\n");
	return;
}

void Pop_Seq(SeqStack* s, Elemtype* e) {
	if (s->top == -1) {
		printf("empty!\n");
		return;
	}
	*e = s->data[s->top];
	s->top--;
	printf("popped.(seq)\n");
	return;
}

void Pop_Link(LinkStack* head, Elemtype* e) {
	if (head->next == 0) {
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

void GetTop_Seq(SeqStack* s, Elemtype* e) {
	if (s->top == -1) {
		printf("empty!\n");
		return;
	}
	*e = s->data[s->top];
	printf("got.(seq)\n");
	return;
}

void GetTop_Link(LinkStack* head, Elemtype* e) {
	if (head->next == 0) {
		printf("empty!\n");
		return;
	}
	*e = head->next->data;
	printf("got.(link)\n");
	return;
}

void exp_to_postexp(char* exp, char* postexp, SeqStack* OptSt) {
	int i = 0;
	char ch;
	Elemtype recv;
	while ((ch = exp[i++]) != '\0') {
		switch (ch) {
			case '(':
				Push_Seq(OptSt, ch);
				break;
			case ')':
				for (Pop_Seq(OptSt, &recv); recv != '('; Pop_Seq(OptSt, &recv))
					strncat(postexp, &recv,1);
				recv = '\0';
				break;
			case '+':
			case '-':
				while (OptSt->top != -1) {
					if (OptSt->data[OptSt->top] != '(') {
						Pop_Seq(OptSt, &recv);
						strncat(postexp, &recv, 1);
						continue;
					} else
						break;
				}
				Push_Seq(OptSt, ch);
				break;
			case '*':
			case '/':
				while (OptSt->top != -1) {
					if (OptSt->data[OptSt->top] != '(' || OptSt->data[OptSt->top] != '+'
					    || OptSt->data[OptSt->top] != '-') {
						Pop_Seq(OptSt, &recv);
						strncat(postexp, &recv, 1);
						continue;
					} else
						break;
				}
				Push_Seq(OptSt, ch);
				break;
		default:
			if (ch >= '0' && ch <= '9') {
				strncat(postexp, &ch, 1);
				continue;
			}else{
				printf("wrong exp. please check.\n");
				return;
			}
			strncat(postexp, "#", 1);
		}
	}
	while (OptSt->top != -1) {
		Pop_Seq(OptSt, &recv);
		strncat(postexp, &recv, 1);
	}
	strncat(postexp, "\0", 1);
}

int main() {
//	LinkStack s;
//	Elemtype e = 0,recv = 0;
//	InitLinkStack(&s);
//	Push_Link(&s,3);
//	GetTop_Link(&s,&e);
//	printf("%d\n",e);
//	Pop_Link(&s,&recv);
//	printf("%d\n",recv);
	char exp[50];
	char postexp[50];
	printf("input exp:");
	scanf("%s", exp);
	SeqStack OptSt;
	InitSeqStack(&OptSt);
	exp_to_postexp(exp, postexp, &OptSt);
	printf("%s\n", postexp);
	return 0;
}
