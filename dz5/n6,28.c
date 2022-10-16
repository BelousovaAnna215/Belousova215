#include<stdio.h>
#include<stdlib.h>

typedef struct Node *list; 
typedef struct Node{
	double elem;
	list next;
} node;

list create(void){
	double k;
	list p;
	scanf("%lf", &k);
	if (k == 0) {
	return NULL;	
	} else {
		p = (list) malloc(sizeof(node));
		p->elem = k;
		p->next=create();
		return p;
	}
}

void print( list p){
	if (p != NULL){
	printf("list: ");
	while (p->next != NULL){
		printf("%f ",p->elem);
		p = p->next;
	}
	printf("%f ",p->elem);
	printf("\n");
}
}

//меняет местами первый и последний элементы списка
void change ( list p){
	list a;
	int buf;
	a = p;
	while (p->next != NULL){
		p = p->next;		
	}
	buf = a->elem;
	a->elem = p -> elem;
	p->elem = buf;
}
 

//удаляет из списка первое вхождение элемента с заданным значением
list del1 ( list p, double a){
	list q,x;
	x = p;
	if ( p->elem == a){
		q = p;
		p = p -> next;
		free(q);
		return p;
	} else {
		while ((p->next->elem != a) && (p->next->next != NULL)){
			p = p->next;
		}
		if (p->next->next != NULL) {
			q = p->next;
			p->next = p->next->next;
			free(q);
		}
		return x;
	}
}



//удаляет все элементы с данным значением
list delall ( list p, double a){
	list x,q;
	x = p;
	while (p->next != NULL){
		if ((p->next->elem != a) && (p->next->next != NULL)){
			p = p->next;
		}
		else{
			if (p->next->next != NULL) {
				q = p->next;
				p->next = p->next->next;
				free(q);
			} else {
				if (p->next->elem == a) {
					q = p->next;
					p->next = NULL;
					free(q);
				}
			}
		}
	}
	if (x->elem == a){
		q = x;
		x = x -> next;
		free(q);
	}
	return x;
}

//добавляет 1 новый элемент
void plusone( list p, double a){
		list q;
		q = p->next;
		p->next = (list) malloc(sizeof(node));
		p->next->elem = a;
		p->next->next = q;
}


//после каждого звена вставляет звено с таким же значением
void copy(list p, double a){
	while (p->next != NULL){
		if (p->elem == a){
			plusone(p,a);
			p = p->next->next;
		} else {
			p = p->next;
		}
	}
	if (p->elem == a){
		plusone(p,a);
	}
}


int main()
{
 list p;
 p = create();
 print(p);
 
 //change(p);
 double a = 1;
// p=del1(p,a);
 //p = delall(p,a);
// plusone(p,a);
 copy(p,a);
 print(p);
 
 return 0;
}
