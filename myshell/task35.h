#ifndef TASK35
#define TASK35

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#define SIZE 16
#define N 10

typedef char ** list;
char ** array_str; // список слов (в виде массива)

char** build_array();
void clearlist(list * array_str);
void printlist(char ** array_str);
void change(char ** array_str);// замена $ИМЯ

#endif
