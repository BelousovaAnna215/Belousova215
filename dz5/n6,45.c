#include<stdio.h>
#include<stdlib.h>
#include "tree45e.h"

typedef struct Node2t *list2t;
typedef struct Node2t{
	int elem;
	list2t left;
	list2t right;
} Node2t;

list2t maketree(){
	static Node2t n23 = {23,NULL,NULL};
	static Node2t n12 = {12,&n23,NULL};
	
	static Node2t n21 = {21,NULL,NULL};
	static Node2t n11 = {11,&n21,NULL};
	static Node2t n0 = {0,&n11,&n12};
	return &n0;	
}

int count_level (list2t p_node, int level){
	int cur_level = 0;
	int amount_elem = 0;
	if (level == 0) return 1;
	if( p_node == NULL || level < 0)
	return 0;
	
	stack st = NULL;
	//putst p_node;
	while(1){
		printf("p_node->elem = %d\n",p_node->elem);

		if (cur_level == level){
			amount_elem += 1;
			//p_node = stack_nodes.top();
			//stack_nodes.pop();
			p_node = getst(&st);
			//p_node = ll->elem;
			cur_level -= 1;
		}else if(p_node->left != NULL ){
			list2t new_p_node = p_node->left;
			p_node->left = NULL;
			//stack_nodes.push(p_node);
			st = putst ( st, (void*)p_node );
			p_node = new_p_node;
			cur_level += 1;
		}else if(p_node->right != NULL ){
			list2t new_p_node = p_node->right;
			p_node->right = NULL;
			//stack_nodes.push(p_node);
			st = putst ( st, (void*)p_node );
			p_node = new_p_node;
			cur_level += 1;
		}else{
			if(cur_level == 0) break;
			//p_node = stack_nodes.top();
			//stack_nodes.pop();
			p_node = getst(&st);
			cur_level -= 1;
 		}
	}	

	return amount_elem;
}

int main(int argc, char **argv)
{
	list p_node = maketree ();
	int amount_elem = count_level (p_node, 3);
	printf("amount_elem = %d",amount_elem);
	return 0;
}
