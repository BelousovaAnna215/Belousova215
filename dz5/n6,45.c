#include<stdio.h>
#include<stdlib.h>

#include "tree45e.h"


typedef struct Nodel *listl;
struct Nodel{
	int elem;
	listl left;
	listl right;
};



stack st;

listl maketree (){
	static struct Nodel n25 = {25,NULL,NULL};
	static struct Nodel n24 = {24,&n25,NULL};
	static struct Nodel n23 = {23,NULL,NULL};
	static struct Nodel n12 = {12,&n23,&n24};
	
	static struct Nodel n21 = {21,NULL,NULL};
	static struct Nodel n11 = {11,&n21,NULL};
	
	static struct Nodel n0 = {0,&n11,&n12};
	return &n0;
}

int count_level (listl p_node, int level){
	int cur_level = 0;
	int amount_elem = 0;
	if (level == 0)	return 1;
	if (p_node == NULL)	return 0;
	putst ( &st, (void*)p_node);
	

	while(1){
		printf("p_node->elem = %d\n",p_node->elem);

		if (cur_level == level){
			amount_elem += 1;
			p_node = (listl)getst(&st);
			cur_level -= 1;
		}else if(p_node->left != NULL ){
			listl new_p_node = p_node->left;
			p_node->left = NULL;
			putst ( &st, (void*)p_node);
			p_node = new_p_node;
			cur_level += 1;
		}else if(p_node->right != NULL ){
			listl new_p_node = p_node->right;
			p_node->right = NULL;
			putst ( &st, (void*)p_node);
			p_node = new_p_node;
			cur_level += 1;
		}else{
			if(cur_level == 0) break;
			p_node = (listl)getst(&st);
			cur_level -= 1;
 		}
	}	

	return amount_elem;
}

int main(void)
{
	listl p_node = maketree ();
	int amount_elem = count_level (p_node, 3);
	printf("amount_elem = %d",amount_elem);
	return 0;
}


