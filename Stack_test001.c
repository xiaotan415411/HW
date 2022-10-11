#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MaxSize 50

typedef char Elemtype;
typedef struct
{
	Elemtype data[MaxSize];
	int top;
} SeqStack;
typedef struct SNode
{
	Elemtype data;
	struct SNode *next;
} LinkStack;
typedef struct
{
	double data[MaxSize];
	int top;
} OptNumStack;

void InitSeqStack(SeqStack *s)
{
	s->top = -1;
}

void InitLinkStack(LinkStack *s)
{
	s->next = 0;
}

void Push_Seq(SeqStack *s, Elemtype x)
{
	if (s->top == MaxSize - 1)
	{
		printf("full!\n");
		return;
	}
	s->top++;
	s->data[s->top] = x;
	printf("pushed %c.(seq)\n",x);
	return;
}

void Push_OptNum(OptNumStack *OptNum, double x)
{
	if (OptNum->top == MaxSize - 1)
	{
		printf("full!\n");
		return;
	}
	OptNum->top++;
	OptNum->data[OptNum->top] = x;
	printf("pushed %f.(seq)\n",x);
	return;
}

void Push_Link(LinkStack *head, Elemtype x)
{
	LinkStack *s = (LinkStack *)malloc(sizeof(LinkStack));
	s->data = x;
	s->next = head->next;
	head->next = s;
	printf("pushed.(link)\n");
	return;
}

void Pop_Seq(SeqStack *s, Elemtype *e)
{
	if (s->top == -1)
	{
		printf("empty!\n");
		return;
	}
	*e = s->data[s->top];
	s->top--;
	printf("popped %c.(seq)\n",*e);
	return;
}

void Pop_Link(LinkStack *head, Elemtype *e)
{
	if (head->next == 0)
	{
		printf("empty!\n");
		return;
	}
	LinkStack *p = head->next;
	*e = p->data;
	head->next = p->next;
	free(p);
	printf("popped %c.(link)\n",*e);
	return;
}

void Pop_OptNum(OptNumStack *s, double *e)
{
	if (s->top == -1)
	{
		printf("empty!\n");
		return;
	}
	*e = s->data[s->top];
	s->top--;
	printf("popped %f.(seq)\n",*e);
	return;
}

void GetTop_Seq(SeqStack *s, Elemtype *e)
{
	if (s->top == -1)
	{
		printf("empty!\n");
		return;
	}
	*e = s->data[s->top];
	printf("got %c.(seq)\n",*e);
	return;
}

void GetTop_Link(LinkStack *head, Elemtype *e)
{
	if (head->next == 0)
	{
		printf("empty!\n");
		return;
	}
	*e = head->next->data;
	printf("got.(link)\n");
	return;
}

void GetTop_OptNum(OptNumStack *s, double *e)
{
	if (s->top == -1)
	{
		printf("empty!\n");
		return;
	}
	*e = s->data[s->top];
	printf("got %f.(seq)\n",*e);
	return;
}

void postexp_calc(char *postexp)
{
	OptNumStack OptNum;
	OptNum.top = -1;
	int i = 0;
	double a = 0, b = 0, temp1 = 0, temp2 = 0, recv = 0;
	char ch;
	while ((ch = postexp[i]) != '\0')
	{
		switch (ch)
		{
		case '+':
			Pop_OptNum(&OptNum, &a);
			Pop_OptNum(&OptNum, &b);
			Push_OptNum(&OptNum, a + b);
			i++;
			break;
		case '-':
			Pop_OptNum(&OptNum, &a);
			Pop_OptNum(&OptNum, &b);
			Push_OptNum(&OptNum, b - a);
			i++;
			break;
		case '*':
			Pop_OptNum(&OptNum, &a);
			Pop_OptNum(&OptNum, &b);
			Push_OptNum(&OptNum, a * b);
			i++;
			break;
		case '/':
			Pop_OptNum(&OptNum, &a);
			Pop_OptNum(&OptNum, &b);
			if (a == 0)
			{
				printf("cant div 0!\n");
				return;
			}
			Push_OptNum(&OptNum, b / a);
			i++;
			break;
		default:
			
			while (ch >= '0' && ch <= '9')
			{
				temp1 = 10 * temp1 + ch - '0';
				ch = postexp[++i];
				if (ch == '.')
				{
					double j = 1.0;
					ch = postexp[++i];
					while (ch >= '0' && ch <= '9')
					{
						temp2 += (ch - '0') / (pow(10.0, j));
						ch = postexp[++i];
						j++;
					}
				}
			}
			Push_OptNum(&OptNum, temp1 + temp2);
			temp1 = temp2 = 0;
			if (ch == '#')
				i++;
			break;
		}
	}
	GetTop_OptNum(&OptNum, &recv);
	printf("%f", recv);
}

void exp_to_postexp(char *exp, char *postexp, SeqStack *OptSt)
{
	int i = 0;
	char ch;
	Elemtype recv;
	while ((ch = exp[i]) != '\0')
	{
		switch (ch)
		{
		case '(':
			Push_Seq(OptSt, ch);
			i++;
			break;
		case ')':
			for (Pop_Seq(OptSt, &recv); recv != '('; Pop_Seq(OptSt, &recv))
				strncat(postexp, &recv, 1);
			i++;
			break;
		case '+':
		case '-':
			while (OptSt->top != -1)
			{
				if (OptSt->data[OptSt->top] != '(')
				{
					Pop_Seq(OptSt, &recv);
					strncat(postexp, &recv, 1);
					continue;
				}
				else
					break;
			}
			Push_Seq(OptSt, ch);
			i++;
			break;
		case '*':
		case '/':
			while (OptSt->top != -1)
			{
				if (OptSt->data[OptSt->top] != '(' && OptSt->data[OptSt->top] != '+' && OptSt->data[OptSt->top] != '-')
				{
					Pop_Seq(OptSt, &recv);
					strncat(postexp, &recv, 1);
					continue;
				}
				else
					break;
			}
			Push_Seq(OptSt, ch);
			i++;
			break;
		case '.':
			strncat(postexp, &ch, 1);
			i++;
			break;
		default:
			if (ch >= '0' && ch <= '9')
			{
				while ((ch >= '0' && ch <= '9') || ch == '.')
				{
					strncat(postexp, &ch, 1);
					ch = exp[++i];
				}
			}
			else
			{
				printf("incorrect exp. please check.\n");
				return;
			}
			strncat(postexp, "#", 2);
		}
	}
	while (OptSt->top != -1)
	{
		Pop_Seq(OptSt, &recv);
		if(recv == '(' || recv == ')'){
			printf("incorrect exp. please check.\n");
			return;
		}
		strncat(postexp, &recv, 1);
	}
	strncat(postexp, "\0", 1);
//	postexp_calc(postexp);
}



int main()
{
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
	postexp_calc(postexp);
//	system("pause");
	return 0;
}
