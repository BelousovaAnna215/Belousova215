#include<stdio.h>
#include<stdlib.h>

typedef struct Node *list;
typedef struct Node{
	void *elem;
	list next;
} node;

list putq ( list p, void *a){
	if ( p == NULL ){
		p = (list)malloc(sizeof(node));
		p->elem = a;
		p->next = NULL;
		return p;
	} else {
		list q = p;
		while (p->next != NULL){
			p = p->next;
		}
		p->next = (list)malloc(sizeof(node));
		p->next->elem = a;
		p->next->next = NULL;
		return q;
	}
}

void *getq (list *p){
	if ( *p == NULL ){
		printf ("No elem");
		return NULL;
	} else {
		void *a = (*p)->elem;
		list q = *p;
		*p = (*p)->next;
		free(q);
		return a;
	}
}


list del_allq (list p){
	list q;
	while (p->next != NULL){
		q = p;
		p = p->next;
		free(q);
	}
	q = p;
	p = NULL;
	free(q);
	return p;
}

int amountq ( list p){
	int a = 0;
	while (p->next != NULL){
		a++;
	}
	a++;
	return a;
} 
