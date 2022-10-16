#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct inode *list; 

struct inode {
	struct data *p; //указатель на структуру с данными
	list next;
} inode;

struct data{
	double f;
	char *s[2];
} data;


list copyl (list l1){
	list l2,q;
	if (l1 == NULL){
		return NULL;
	} else {
		l2 = (list)malloc(sizeof(inode));
		l2 = l1;
		q = l2;
		l1 = l1->next;
		l2 = l2->next; 
		while ( l1->next != NULL){
			l2 = (list)malloc(sizeof(inode));
			l2 = l1;
			l1 = l1->next;
			l2 = l2->next; 
		}
		l2 = (list)malloc(sizeof(inode));
		l2 = l1;
		return q;
	}
} 

