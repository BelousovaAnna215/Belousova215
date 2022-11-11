#include<stdio.h>
#include<stdlib.h>

typedef struct Node *list; 
typedef struct Node{
	int elem;
	list next;
} node;

list create(void){
	int k;
	list p;
	scanf("%d", &k);
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
			printf("%d ",p->elem);
			p = p->next;
		}
		printf("%d ",p->elem);
		printf("\n");
	} else printf("void list\n");
}



list createL3 ( list l1, list l2){
	int fl = 0;
	list buf, l3;
	if (l1 == NULL){
		buf = l1;
		l1 = l2;
		l2 = buf;
		if (l1 == NULL) return NULL;
	}
	l3 = (list)malloc(sizeof(node));
	buf = l3;
	while ( l1->next != NULL){
		buf->elem = l1->elem;
		buf->next = (list)malloc(sizeof(node));
		buf = buf->next;
		l1 = l1->next;
	}
	buf->elem = l1->elem;
	buf->next = NULL;
	while (l2 != NULL){
		fl = 0;
		buf = l3;
		if (buf == NULL){
			l3 = (list)malloc(sizeof(node));
			buf = l3;
			while ( l2 != NULL){
				buf->elem = l2->elem;
				buf->next = (list)malloc(sizeof(node));
				buf = buf->next;
				l2 = l2->next;
			}
			break;
		}
		while (buf->next != NULL){
			if(l3->elem == l2->elem){
				list q = l3;
				l3 = l3->next;
				buf = l3;
				free(q);
				fl = 1;
			} else {
				if(buf->next->elem == l2->elem){
					list q = buf->next;
					fl = 1;
					if ( buf->next->next == NULL){
						buf->next = NULL;
						break;
					} else {
						buf->next = buf->next->next;
					}
					free(q);
				} else {
					buf = buf->next;
				}
			}
		}
		
		if( l3 != NULL && l3->elem == l2->elem ){
			list q = l3;
			l3 = l3->next;
			buf = l3;
			free(q);
			fl = 1;
		}
		if (fl == 0){
			list q = l3;
			l3 = (list)malloc(sizeof(node));
			l3->elem = l2->elem;
			l3->next = q;
		}		
		l2 = l2->next;
	}
	return l3;
}

int main()
{
 list l1,l2,l3;
 l1 = create();
 print(l1);
 l2 = create();
 print(l2);
 l3 = createL3(l1, l2);
 print(l3);
 
 return 0;
}

