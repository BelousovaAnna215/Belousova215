#include<stdio.h>
#include<stdlib.h>

typedef struct Node *list;
typedef struct Node{
	void *elem;
	list next;
} node;

void putst (list *po, void *value)
{
	list newp = (list)malloc(sizeof(node));
	newp->elem = value;
	newp->next = *po;
	*po = newp;
}

void *getst(list *po)
{
    if (*po == NULL){
        return NULL;
    }
    list newp = *po;
    void *value = newp->elem;
    *po = (*po)->next;
    free(newp);
    return value;
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


