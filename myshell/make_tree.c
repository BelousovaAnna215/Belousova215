#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "make_tree.h"

list plex; // указатель текущей лексемы
Tree beg_cmd; 
Tree cur_cmd; 
Tree prev_cmd; 
Tree conv_cmd; 

Tree make_cmd();//Функция создает дерево из одного элемента, обнуляет все поля
void add_arg();//Функция добавляет очередной элемент в массив argv текущей команды
void conv(list plex);
void conv1(list plex);
void convp(list plex);
void backgrnd(list plex);
void out(list plex);
void in(list plex);

void ClearArgv(list *lst);
void clear_tree( Tree t );
void print_argv(list p);
void print_tree(Tree t);
Tree make_cmd();
void add_arg(Tree t, char *plex);
void make_bgrnd(Tree t);
int IsBadSymFile(char * str);
Tree make_tree (list plex);


//Функция освобождает память, занимаемую списком (если он не пуст), и делает список пустым.
void ClearArgv(list *lst){
    int i;
    if (*lst == NULL)
	    return;
    for (i = 0; *(*lst + i) != NULL; i++)
      free( *(*lst + i) );
    free(*lst);
    *lst = NULL;
  }


//Функция освобождает память, занимаемую структурой (деревом), и делает ее пустой.
void clear_tree( Tree t ){
    if (t == NULL)
      return;
    clear_tree( t->pipe );
    clear_tree( t->next );
    ClearArgv(&(t->argv));
    free(t);
}


//Функция печатает элементы списка argv
void print_argv(list p){
    list q = p;
    if (p != NULL){
        while(*p != NULL){
            printf("argv[%d]=%s\n",(int)(p-q), *p);
            p++;
        }
    }
}


//Функция печатати дерева
void print_tree(Tree t){
	printf("______________________\n");
	printf("Tree is:\n");
    list p;
    if(t == NULL) return;

    p = t->argv;
    if(p != NULL)
      print_argv(p);
    else {
        printf("psubshell\n");
    }
    if(t->infile == NULL)
		printf("infile = NULL\n");
    else
		printf("infile = %s\n", t->infile);
    if(t->outfile==NULL)
		printf("outfile = NULL\n");
    else
		printf("outfile = %s\n", t->outfile);
    fprintf(stderr, "background=%d\n", t->backgrnd);
    if(t->pipe == NULL)
      printf("pipe=NULL \n");
    else {
		printf("pipe---> \n");
        print_tree(t->pipe);
    }
    if(t->next == NULL)
		printf("next=NULL \n");
    else {
        printf("next---> \n");
        print_tree(t->next);
    }
    printf("end tree\n");
    printf("______________________\n");
}


// Функция создает дерево из одного элемента, обнуляет все поля
Tree make_cmd(){
    Tree t;
    t = malloc(sizeof(*t));
    t->argv = NULL;
    t->infile = NULL;
    t->outfile = NULL;
    t->backgrnd = 0;
    t->pipe = NULL;
    t->next = NULL;
    return t;
}

//Функция добавляет очередной элемент в массив argv текущей команды
void add_arg(Tree t, char * plex){
    list p;
    int cnt = 0; 
    if (t->argv == NULL){
        if ( ( t->argv = realloc(t->argv, 2*sizeof(char *)) ) == NULL){
            printf("не выделяется память");
            clear_tree(t);
            return;
         }
        if ( ( *(t->argv) = malloc( (strlen(plex)+1)*sizeof(char) ) ) == NULL ){
            printf("не выделяется память");
            clear_tree(t);
            return;
         }
        strcpy(*(t->argv), plex);
        *(t->argv+1) = NULL;
      } else {
        p = t->argv;
        while (*p != NULL){
            cnt++;
            p++;
        }
        if ( ( t->argv = realloc(t->argv, (cnt+2)*sizeof(char *)) ) == NULL ){
            printf("не выделяется память");
            clear_tree(t);
            return;
        }
        if ( ( *(t->argv+cnt) = malloc( (strlen(plex)+1)*sizeof(char) ) ) == NULL){
            printf("не выделяется память");
            clear_tree(t);
            return;
         }
        strcpy(*(t->argv+cnt), plex);
        *(t->argv+cnt+1) = NULL;
      }
}


// Функция устанавливает поле backgrnd=1 во всех командах конвейера t
void make_bgrnd(Tree t){
    t->backgrnd = 1;
    if(t->pipe != NULL)
		make_bgrnd(t->pipe);
}

// Функция определяет нежелательные символы
int IsBadSymFile(char * str){
	if (str == NULL ||
		strcmp(str, "|") == 0 ||
        strcmp(str, ";") == 0 ||
        strcmp(str, "&") == 0 ||
        strcmp(str, ">") == 0 ||
        strcmp(str, "<") == 0 )
      return 1;
    else
      return 0;
}

Tree make_tree ( list plex ){
	if (plex == NULL){
		beg_cmd = NULL; // дерево вида NULL
		return NULL;
	} else {
		if (strcmp(*plex, "|") == 0 || strcmp(*plex, "&") == 0 || strcmp(*plex, ";") == 0){ 
			printf("error");
			beg_cmd = NULL;
			clear_tree(beg_cmd);
			return NULL;
		}
		beg_cmd = make_cmd();
		cur_cmd = beg_cmd;
		prev_cmd = cur_cmd;
		conv_cmd = beg_cmd;
		conv(plex);
		return beg_cmd;
	}
}

void conv(list plex){
	//printf("conv\n");
	if (*plex == NULL){
		return;
		//end();
	} else if (strcmp(*plex, ";") == 0){
		plex++;
		convp(plex);
	} else if (strcmp(*plex, "&") == 0){
		plex++;
		backgrnd(plex);
	} else if (strcmp(*plex, ">") == 0){
		plex++;
		out(plex);
	} else if (strcmp(*plex, "<") == 0){
		plex++;
		in(plex);
	} else if (strcmp(*plex, "|") == 0){
		plex++;
		conv1(plex);
	} else {
		add_arg(cur_cmd, *plex );
		plex++;
		conv(plex);
	}
}

// |
void conv1(list plex){
	if (strcmp(*plex, "|") == 0 || strcmp(*plex, "&") == 0 || strcmp(*plex, ";") == 0 || *plex==NULL){
		printf("error");
        clear_tree(beg_cmd);
		return;
    }
	cur_cmd = make_cmd();
	prev_cmd->pipe = cur_cmd;
	prev_cmd = cur_cmd;
    conv(plex);
}

// ;
void convp(list plex){
	if (*plex == NULL){
		return;
	}
	if (strcmp(*plex, "|") == 0 || strcmp(*plex, "&") == 0 || strcmp(*plex, ";") == 0 || *plex==NULL){
		printf("error");
        clear_tree(beg_cmd);
		return;
    }
	cur_cmd = make_cmd();
	conv_cmd->next = cur_cmd;
	prev_cmd = cur_cmd;
	conv_cmd = cur_cmd;
    conv(plex);
}

//&
void backgrnd(list plex){
	if (*plex == NULL){
		make_bgrnd(conv_cmd);
		return ;
	} else {
		if (strcmp(*plex, "|") == 0 || strcmp(*plex, "&") == 0 || strcmp(*plex, ";") == 0){
			printf("error");
            clear_tree(beg_cmd);
		    return ;
        }
		make_bgrnd(conv_cmd);
		cur_cmd = make_cmd();
		conv_cmd->next = cur_cmd;
		prev_cmd = cur_cmd;
		conv_cmd = cur_cmd;
		conv(plex);
	}
}

//<
void in(list plex){
	if (IsBadSymFile(*plex)){
		printf("error");
		clear_tree(beg_cmd);
		return;
	}
	cur_cmd->infile = *plex;
	plex++;
	conv(plex);
}

//>
void out(list plex){
	if (IsBadSymFile(*plex)){
		printf("error");
		clear_tree(beg_cmd);
		return;
	}
	cur_cmd->outfile = *plex;
	plex++;
	conv(plex);
}

/*
int main(){
	char* plex[] = {"date",";","cat","|","date",";", "pwd", ">", "zz", NULL};
	//plex = build_array();
	//printf("%s\n", cmds[0]);
	//print_argv(cmds);
	Tree t = make_tree (plex);
	print_tree(t);
	//ClearArgv(&cmds);
	//print_argv(cmds);
}
*/
