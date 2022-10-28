#include<stdio.h>
#include<stdlib.h>
#include "tree45e.h"

typedef struct Node2t *list2t;
typedef struct Node2t{
        int elem;
        list2t left;
        list2t right;
} Node2t;

int count_level (list2t p_node, int level){
        int cur_level = 0;
        int amount_elem = 0;
        if (level == 0) return 1;
        if( p_node == NULL || level < 0)
        return 0;

        stack st = NULL;
        while(1){
                if (cur_level == level){
                        amount_elem += 1;
                        p_node = getst(&st);
                        cur_level -= 1;
		}else if(p_node->left != NULL ){
                        list2t new_p_node = p_node->left;
                        p_node->left = NULL;
                        st = putst ( st, (void*)p_node );
                        p_node = new_p_node;
                        cur_level += 1;
                }else if(p_node->right != NULL ){
                        list2t new_p_node = p_node->right;
                        p_node->right = NULL;
                        st = putst ( st, (void*)p_node );
                        p_node = new_p_node;
                        cur_level += 1;
                }else{
                        if(cur_level == 0) break;
                        p_node = getst(&st);
			cur_level -= 1;
                }
        }
        return amount_elem;
}

