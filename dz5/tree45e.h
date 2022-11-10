#ifndef TREE6P45E
#define TREE6P45E
#define  Eem_type void*



typedef struct Node *list;
typedef struct Node{
	Eem_type elem;
	list next;
} node;

typedef list stack;

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

#endif
