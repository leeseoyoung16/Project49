#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef char element;
typedef struct DListNode {
	element data[1000];
	struct DListNode* llink;
	struct DListNode* rlink;
}DListNode;

// 초기화
void init(DListNode* phead) {
	phead->llink = phead;
	phead->rlink = phead;
}

// 삽입 연산
void dinsert(DListNode* before, element* data) {
	DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
	strcpy_s(newnode->data, strlen(data) + 1, data);
	newnode->llink = before;
	newnode->rlink = before->rlink;
	before->rlink->llink = newnode;
	before->rlink = newnode;
}

// 삭제 연산
void ddelete(DListNode* head, DListNode* removed) {
	if (removed == head) return;
	removed->llink->rlink = removed->rlink;
	removed->rlink->llink = removed->llink;
	free(removed);
}

// 프린트
void print_dlist(DListNode* head, DListNode* currently) {
	DListNode* temp = head->rlink;
	while (temp != head) {
		printf("%s", temp->data);
		if (temp == currently) {
			printf(" [o]");
		}
		temp = temp->rlink;
		printf("\n");
	}
	
}

int main(void) {
	DListNode* head = (DListNode*)malloc(sizeof(DListNode));
	DListNode* currently = NULL;

	init(head);
	char select;
	char fruit[100];
	while (1) {
		printf("==== Menu ====\n");
		printf("n) next fruit\n");
		printf("p) previous fruit\n");
		printf("d) delete the current fruit\n");
		printf("i) insert fruit after current fruit\n");
		printf("o) output the fruit list (Output [o] at the end of the currently selected node)\n");
		printf("e) exit the program\n");
		printf("=============\n");
		printf("select a menu: ");
		scanf_s(" %c", &select,sizeof(select));

		if (select == 'n') {
			currently = currently->rlink;
		}
		else if (select == 'p') {
			currently = currently->llink;
		}
		else if (select == 'd') {
			currently = currently->rlink;
			ddelete(head, currently->llink);
		}
		else if (select == 'i') {
			printf("Enter the name of the fruit to add: ");
			scanf_s(" %s", fruit,sizeof(fruit));
			if (currently != NULL) {
				dinsert(currently, fruit);
			}
			else {
				dinsert(head, fruit);
				currently = head->rlink;
			}

		}
		else if (select == 'o') {
			print_dlist(head, currently);
		}
		else if (select == 'e') {
			printf("Exit the program\n");
			exit(1);
		}
		else {
			printf("Invalid menu.\n");
		}
		printf("\n");
	}

	return 0;
}
