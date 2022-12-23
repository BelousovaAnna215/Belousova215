#include "task35.h"
#include "make_tree.h"
#include "exec.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void inv(){
	printf("%s", "\033[35m");
	char s[100];
	gethostname(s, 100);
	printf("%s@%s", getenv("USER"), s);
	printf("%s", "\033[01;37m");
	getcwd(s, 100);
	printf(":%s\n$ ", s);
	fflush(stdout);
}
 void sig_handler(int a){
	 printf("\n");
	 inv();
 }

int main()
  {
    list lst = NULL;
    Tree cmd_tree = NULL;
    pidlist plst = NULL;
    
    signal(SIGINT, sig_handler);
    
    printf("Begin of proga\n");
    while (1){
        clear_tree(cmd_tree);  //очистка дерева
        ClearArgv(&lst);   //очистка списока лексем
        
        clear_zombie(&plst); //очистить_зомби из списка (таблицы) зарегистрированных фоновых процессов;
        
        inv();
        lst = build_array();  //запрашиваем у пользователя очередную строку с командой, разбиваем ее на лексемы (строим array_str)
        printf("thanks tor str\n");
        printlist(lst);
        printf("end of array_str\n");
        
        if (lst == NULL) {
			printf("lst is NULL\n");
            del_all_pid(plst);
            //return 0;
        }
        
        printf("we need some chandes\n");
        change (lst);   //заменяем в списке строки вида $ИМЯ
        printf("changes is amazing\n");
        printlist(lst);
    	
    	printf("start to make tree\n");
        cmd_tree = make_tree(lst);   //по списку лексем строим дерево
        printf("ready, print tree\n");
		print_tree(cmd_tree); 
        
        exec_com(cmd_tree, &plst);//выполнить команду, обходя дерево и создавая соответствующие процессы, файлы, каналы;
    
        printf("completed\n");
      }
  }
