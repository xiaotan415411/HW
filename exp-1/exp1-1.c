#include<stdio.h>
#include<stdlib.h>

typedef char ElemType;
typedef struct SNode {
	ElemType data;
	struct SNode* next;
} SLinkNode;

SLinkNode* InitLink() {
	SLinkNode* h = (SLinkNode*)malloc(sizeof(SLinkNode));
	h->next = 0;
	return h;
}

void InsertData_backward(SLinkNode* h, ElemType data) {
	SLinkNode* s = h;
	while (s->next != 0) {
		s = s->next;
	}
	SLinkNode* p = (SLinkNode*)malloc(sizeof(SLinkNode));
	p->data = data;
	p->next = 0;
	s->next = p;
}

void PrintLength(SLinkNode* h) {
	SLinkNode* p = h;
	int count = 0;
	while ((p = p->next) != 0)
		count++;
	printf("the length is %d\n", count);
}

void isEmpty(SLinkNode* h) {
	if (h->next == 0)
		printf("link is empty.\n");
	else
		printf("link isn't empty.\n");
}

void PrintElem(SLinkNode* h, int loc) {
	if (loc <= 0) {
		printf("%d is an invaild location!\n", loc);
		return;
	}
	SLinkNode* p = h;
	for (int i = 0; i < loc; i++) {
		p = p->next;
		if (p == 0) {
			printf("less than %d node!\n", loc);
			return;
		}
	}
	printf("the ");
	switch (loc % 10) {
		case 1:
			printf("%dst element is %c\n", loc, p->data);
			break;
		case 2:
			printf("%dnd element is %c\n", loc, p->data);
			break;
		case 3:
			printf("%drd element is %c\n", loc, p->data);
			break;
		default:
			printf("%dth element is %c\n", loc, p->data);
	}
}

void PrintLocation(SLinkNode* h, ElemType a) {
	SLinkNode* p = h;
	int loc = 0;
	while ((p = p->next) != 0) {
		loc++;
		if (p->data == a) {
			printf("Element %c is in Node_%d\n", a, loc);
			return;
		}
	}
	printf("Element A not found!\n");
	return;
}

void InsertBeforeElem(SLinkNode* h, ElemType f, int loc) {
	if (loc <= 0) {
		printf("%d is a invaild location!\n", loc);
		return;
	}
	SLinkNode* p = h;
	for (int i = 0; i < loc - 1; i++) {
		p = p->next;
		if (p == 0) {
			printf("less than %d node!\n", loc);
			return;
		}
	}
	if (p->next == 0) {
		printf("less than %d node!\n", loc);
		return;
	}
	SLinkNode* s = (SLinkNode*)malloc(sizeof(SLinkNode));
	s->data = f;
	s->next = p->next;
	p->next = s;
	return;
}

void PrintLink(SLinkNode* h) {
	SLinkNode* p = h;
	while ((p = p->next) != 0) {
		printf("%c ", p->data);
	}
	printf("\n");
}

void DeleteElem(SLinkNode* h, int loc) {
	if (loc <= 0) {
		printf("%d is a invaild location!\n", loc);
		return;
	}
	SLinkNode* p = h->next, *s = h;
	for (int i = 1; i < loc; i++) {
		if (p == 0) {
			printf("less than %d node!\n", loc);
			return;
		}
		p = p->next;
		s = s->next;
	}
	if (p->next == 0) {
		s->next = 0;
		free(p);
		printf("Deleted.\n");
		return;
	} else {
		s->next = p->next;
		free(p);
		printf("Deleted.\n");
		return;
	}
}

void ReleaseLink(SLinkNode* h) {
	SLinkNode* p = h->next, *s = h;
	while (p != 0) {
		free(s);
		s = p;
		p = p->next;
	}
	free(s);
	printf("Released.\n");
	return;
}

int main() {
	SLinkNode* h = InitLink();
	InsertData_backward(h, 'a');
	InsertData_backward(h, 'b');
	InsertData_backward(h, 'c');
	InsertData_backward(h, 'd');
	InsertData_backward(h, 'e');
	PrintLink(h);
	PrintLength(h);
	isEmpty(h);
	PrintElem(h, 5);
	PrintLocation(h, 'a');
	InsertBeforeElem(h, 'f', 4);
	PrintLink(h);
	DeleteElem(h, 3);
	PrintLink(h);
	ReleaseLink(h);
	return 0;
}










