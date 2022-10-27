#ifndef TREE6P45E
#define TREE6P45E
//struct Node2t;
//typedef struct Eem_type int;
#define  Eem_type void*
//#define  Eem_type Node2t*


typedef struct Node *list;
typedef struct Node{
	//int elem;
	Eem_type elem;
	list next;
} node;

typedef list stack;

list putst ( list p, Eem_type a){
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

list* getst (list *po){
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

#endif
