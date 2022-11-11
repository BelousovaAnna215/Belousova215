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
	}
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
		//printf("go1\n");
		buf->elem = l1->elem;
		//buf = buf->next;
		//buf = (list)malloc(sizeof(node));
		buf->next = (list)malloc(sizeof(node));
		buf = buf->next;
		l1 = l1->next;
	}
	buf->elem = l1->elem;
	buf->next = NULL;
	print(l3);
	while (l2 != NULL){
		fl = 0;
		buf = l3;
		/*  
		 while (buf != NULL){
			if(buf->elem == l2->elem){
				//нужно удалить этот элемент
				printf("same\n");
				break;
			}
			buf = buf->next;
		}
		*/
		while (buf->next != NULL){
			if(l3->elem == l2->elem){
				list q = l3;
				l3 = l3->next;
				free(q);
				fl = 1;
				buf = buf->next;
			} else {
				if(buf->next->elem == l2->elem){
					list q = buf->next;
					fl = 1;
					if ( buf->next->next == NULL){
						buf = NULL;
					} else {
							buf = buf->next->next;
					}
					free(q);
					printf("same\n");
					break;
				}
				buf = buf->next;
			}
		}
		//if (buf->next == NULL){
		if (fl == 0){
			printf("go3\n");
			list q = l3;
			l3 = (list)malloc(sizeof(node));
			l3->elem = l2->elem;
			l3->next = q;
			printf("after +1\n");
			print(l3);
		}
		printf("go2\n");	
		print(l3);		
		l2 = l2->next;
	}
	printf("end\n");
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

