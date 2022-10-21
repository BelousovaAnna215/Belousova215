#include<stdio.h>
#include<stdlib.h>

typedef struct Node *list;
typedef struct Node{
	void *elem;
	list next;
} node;

list putst ( list p, void *a){
	if ( p == NULL ){
		p = (list)malloc(sizeof(node));
		p->elem = a;
		p->next = NULL;
		return p;
	} else {
		list q = p;
		p = (list)malloc(sizeof(node));
		p->next = q;
		p->elem = a;
		return p;
	}
}

list *getst (list *po){
	if ( (*po) == NULL){
		return NULL;
	} else {
		list p=*po;
		if ( p->next == NULL){
			void *a = p->elem;
			list q = p;
			p = NULL;
			free(q);
			return a;
		} else {
			while (p->next->next != NULL){
				p = p->next;
			}
			void *a = p->next->elem;
			list q = p->next;
			p->next = NULL;
			free(q);
			return a;
		}
	}
}


list del_allst (list p){
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


