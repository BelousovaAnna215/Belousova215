#ifndef MAKE_TREE
#define MAKE_TREE

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include "task35.h"

typedef char ** list;

// дерево
struct cmd_inf {
    list argv; //список из имени команды и аргументов
    char *infile; // файл стандартного ввода
    char *outfile; //файл стандартного вывода
    int backgrnd; //=1, если команда подлежит выполнению в фоновом режиме
    struct cmd_inf *pipe; //следующая команда после “|”
    struct cmd_inf *next; // следующая после “;” (или после “&”)
};

typedef struct cmd_inf * Tree;

list plex;

void clear_tree( Tree t ); // очистка памяти дерева
void ClearArgv(list *lst); // очистка памяти списка
void print_tree(Tree t); 
void print_argv(list p); 
Tree make_tree (list plex); // построение дерева

#endif
