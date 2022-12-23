#ifndef EXEC
#define EXEC

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include "task35.h"
#include "make_tree.h"

struct listforpid {
    int pid;
    struct listforpid *next;
 };
 
typedef struct listforpid * pidlist;

void exec_com(Tree cmd_tree, pidlist * plst);
void del_all_pid(pidlist p);
void print_pid(pidlist p);
void clear_zombie(pidlist *p);


#endif
