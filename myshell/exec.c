#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include "exec.h"



int count(Tree t);
void exec_conv(int count, Tree cmd_tree, int IsBack, pidlist * back_list);
void exec_com(Tree cmd_tree, pidlist * plst);
int count_next(Tree t);
void exec_cd(char ** argv);
void exec_pwd();
void exec_exit();
void exec_mv(char ** argv);
void exec_wc(char ** argv);
void exec_tail(char** argv);
void change_in(Tree t);
void change_out(Tree t);
void del_all_pid(pidlist p);
void print_pid(pidlist p);
void add_pid(pidlist * p, int elem);
void clear_zombie(pidlist *p);
void del_pid(pidlist *p, int pid);

// количество команд конвейера 
int count(Tree t){
    int i;
    if (t == NULL) 
	    return 0;
    for (i=1; t->pipe != NULL; i++)
      t=t->pipe;
    return i;
}

// pr1 | pr2 |pr3 .. prn реализация конвейера
void exec_conv(int count, Tree cmd_tree, int IsBack, pidlist * back_list){
	int fd[2], in, out, next_in;
	int i, fback;
	pid_t pid;
	Tree tree1;
	pidlist l_wait = NULL;
	pidlist p;
	
	tree1 = cmd_tree; // дерево команды
	
	if (count == 0) return;
	if (count == 1) {
		if (strcmp(tree1->argv[0], "cd") == 0 ){
			//выполнение команды cd 
			exec_cd(tree1->argv);
            return ;
		}
		if (strcmp(tree1->argv[0], "pwd") == 0 ){
			//выполнение команды pwd 
			exec_pwd(tree1->argv);
            return ;
		}
		if (strcmp(tree1->argv[0], "exit") == 0 ){
			//выполнение команды exit 
			exec_exit(tree1->argv);
            return ;
		}
		if (strcmp(tree1->argv[0], "mv") == 0 ){
			//выполнение команды mv 
			exec_mv(tree1->argv);
            return ;
		}
		if (strcmp(tree1->argv[0], "wc") == 0 ){
			//выполнение команды wc 
			exec_wc(tree1->argv);
            return ;
		}
		if (strcmp(tree1->argv[0], "tail") == 0 ){
			//выполнение команды tail 
			exec_tail(tree1->argv);
            return ;
		}
		
		if ((pid = fork()) == 0 ){
			
			if (IsBack) //запуск в фоновом режиме
              signal(SIGINT, SIG_IGN);// игнорирование сигнала прерывания
              
            if (tree1->infile != NULL)
              change_in(tree1);
            if (tree1->outfile != NULL)
              change_out(tree1);
              
            // стандартный поток ввода перенаправляется в нулевой файл
            if (IsBack){
                fback = open("/dev/null", O_RDONLY);
                dup2(fback, 0);
                close(fback);
            }
			execvp(tree1->argv[0],tree1->argv); 
            printf("не удалось выполнить команду %s\n", tree1->argv[0]);
            exit(-1);
		}// конец сына
		
		if (IsBack){
            printf("процесс %d работает в фоновом режиме\n", pid);
            add_pid(back_list, pid);
        } else {
            waitpid(pid, 0, 0);
        }
        return ;
		
  }
// >1 команды	
	pipe(fd);
	out = fd[1];
	next_in = fd[0];
	
	if (strcmp(tree1->argv[0], "cd") == 0)
		exec_cd(tree1->argv);
    else if (strcmp(tree1->argv[0], "pwd") == 0 )
		exec_pwd(tree1->argv);
	else if (strcmp(tree1->argv[0], "exit") == 0 )
		exec_exit(tree1->argv);
	else if (strcmp(tree1->argv[0], "mv") == 0 )
		exec_mv(tree1->argv);
	else if (strcmp(tree1->argv[0], "wc") == 0 )
		exec_wc(tree1->argv);
	else if (strcmp(tree1->argv[0], "tail") == 0 )
		exec_tail(tree1->argv);
    else {
	
		if ((pid =fork()) == 0){
			
			if (IsBack)
				signal(SIGINT, SIG_IGN);
				  
			close(next_in);
			dup2(out,1);
			close(out);
			
			if (tree1->infile != NULL)
				change_in(tree1);
			if (tree1->outfile != NULL)
				change_out(tree1);
			if (IsBack){
				fback = open("/dev/null", O_RDONLY);
				dup2(fback, 0);
				close(fback);
			}
			
			execvp(tree1->argv[0],tree1->argv); 
			printf("не удалось выполнить команду %s\n", cmd_tree->argv[0]);
			exit(-1);
		}
		
		if (IsBack){
			printf("процесс %d работает в фоновом режиме\n", pid);
			add_pid(back_list, pid);
		} else {
			add_pid(&l_wait, pid);
		}    
	}
	
	in = next_in;
	for (i = 1; i < count - 1; i++){
		tree1 = tree1->pipe;
		close(out);
		pipe(fd);
		out = fd[1];
		next_in = fd[0];
		
		if ((pid = fork()) == 0){
			if (IsBack)
              signal(SIGINT, SIG_IGN);
			
			close(next_in);
			dup2(in,0);
			close(in);
			dup2(out,1);
			close(out);
			
			if (tree1->infile != NULL)
              change_in(tree1);
            if (tree1->outfile != NULL)
              change_out(tree1);
			
			execvp(tree1->argv[0], tree1->argv); 
            printf("не удалось выполнить команду %s\n", tree1->argv[i]);
            exit(-1);
		}
		if (IsBack){
            printf("процесс %d работает в фоновом режиме\n", pid);
            add_pid(back_list, pid);
        } else {
            add_pid(&l_wait, pid);
        }
		
		close(in);
		in = next_in;
	}// конец цикла
	
	close(out);
	tree1 = tree1->pipe;
	
	if (strcmp(tree1->argv[0], "cd") == 0){
        exec_cd(tree1->argv);
        if (!IsBack){
            print_pid(l_wait);
            p = l_wait;
            while (p != NULL){
                waitpid(p->pid, 0, 0);
                p = p->next;
			}
			del_all_pid(l_wait);
		}
		return ;
    }
    if (strcmp(tree1->argv[0], "pwd") == 0){
        exec_pwd(tree1->argv);
        if (!IsBack){
            print_pid(l_wait);
            p = l_wait;
            while (p != NULL){
                waitpid(p->pid, 0, 0);
                p = p->next;
			}
			del_all_pid(l_wait);
		}
		return ;
    }
    if (strcmp(tree1->argv[0], "exit") == 0){
        exec_exit(tree1->argv);
        if (!IsBack){
            print_pid(l_wait);
            p = l_wait;
            while (p != NULL){
                waitpid(p->pid, 0, 0);
                p = p->next;
			}
			del_all_pid(l_wait);
		}
		return ;
    }
    if (strcmp(tree1->argv[0], "mv") == 0){
        exec_mv(tree1->argv);
        if (!IsBack){
            print_pid(l_wait);
            p = l_wait;
            while (p != NULL){
                waitpid(p->pid, 0, 0);
                p = p->next;
			}
			del_all_pid(l_wait);
		}
		return ;
    }
    if (strcmp(tree1->argv[0], "wc") == 0){
        exec_wc(tree1->argv);
        if (!IsBack){
            print_pid(l_wait);
            p = l_wait;
            while (p != NULL){
                waitpid(p->pid, 0, 0);
                p = p->next;
			}
			del_all_pid(l_wait);
		}
		return ;
    }
    if (strcmp(tree1->argv[0], "tail") == 0){
        exec_tail(tree1->argv);
        if (!IsBack){
            print_pid(l_wait);
            p = l_wait;
            while (p != NULL){
                waitpid(p->pid, 0, 0);
                p = p->next;
			}
			del_all_pid(l_wait);
		}
		return ;
    }
	
	if ((pid = fork()) == 0){
		
		if (IsBack)
          signal(SIGINT, SIG_IGN);
          
		dup2(in,0);
		close(in);
		
		if (tree1->infile != NULL)
          change_in(tree1);
        if (tree1->outfile != NULL)
          change_out(tree1);
          
		execvp(tree1->argv[0], tree1->argv); 
        printf("не удалось выполнить команду %s\n", tree1->argv[count-1]);
        exit(-1);
	}
	close(in);
	
	if (IsBack)
      {
        printf("процесс %d работает в фоновом режиме\n", pid);
        add_pid(back_list, pid);
      } else {
        add_pid(&l_wait, pid); 
        print_pid(l_wait);
        p = l_wait;
        while (p != NULL){
            waitpid(p->pid, 0, 0);
            p = p->next;
        }
        del_all_pid(l_wait);
      }  
	return;
}

//функция проверяет все поля next и вызывет exec_conv
void exec_com(Tree cmd_tree, pidlist * plst){
    Tree tree1;
    int cnt_next, i;
    
    tree1 = cmd_tree;
    cnt_next = count_next(tree1);
    
    for (i=0; i < cnt_next; i++){
        if (tree1->backgrnd){
            exec_conv(count(tree1), tree1, 1, plst);
        } else {
            exec_conv(count(tree1), tree1, 0, plst);
        }
        tree1 = tree1->next;
    }
    return ;
}



// количество команд через ;
int count_next(Tree t){
    int i;
    if (t == NULL) 
	    return 0;
    for (i=1; t->next != NULL; i++)
      t = t->next;
    return i;
}


// функция обработки команды cd
void exec_cd(char ** argv){
	if (argv[1] != NULL && argv[2] != NULL)
      printf("не совпадает число параметров в команде cd\n");
    else {
		if (argv[1] != NULL){
          if (chdir(argv[1]) == -1)
            printf("не удалось выполнить команду cd\n");
          else ;
		} else {
          if (chdir("/") == -1)
            printf("не удалось выполнить команду cd\n");
          else ;
        }
    }
    return;
}

// функция обработки команды pwd, печатает путь до текущего каталога
char *get_current_dir_name(void);
void exec_pwd(){
	printf("%s\n",  get_current_dir_name());
	return;
}

// функция обработки команды exit
void exec_exit(){
	exit(0);
}

// mv 1name 2name функция обработки команды mv
void exec_mv(char ** argv){
	if (argv[1] != NULL && argv[2] != NULL && argv[3] == NULL){
		rename(argv[1],argv[2]);
	} else {
		printf("не удалось выполнить команду mv\n");
	}
	return;
}

// обработка wc
void exec_wc(char ** argv){
	if (argv[1] != NULL && argv[2] == NULL){
		int sym = 0;
		int word = 0;
		int str = 0;
		char s[255];
		char c;
		FILE *fil;
		fil = fopen(argv[1], "r");
		if (fil == NULL){
			printf("error\n");
		} else {
			while ( fscanf(fil, "%c", &c) != EOF ){
				sym++;
				if (c == '\n') str++;
			}
			fseek (fil, 0, SEEK_SET);
			while (fscanf(fil, "%s", s) != EOF){
				word++;
			}
			fclose(fil);
			printf("%d %d %d %s\n", str, word, sym, argv[1]);
		}
	} else {
		printf("не удалось выполнить команду wc\n");
	}
	return;
}

//tail filename
void exec_tail(char** argv){
	if (argv[1] != NULL && argv[2] == NULL){
		int str = 0,str1;
		char s[255];
		char c;
		FILE *fil;
		fil = fopen(argv[1], "r");
		if (fil == NULL){
			printf("error\n");
		} else {
			while ( fscanf(fil, "%c", &c) != EOF ){
				if (c == '\n') str++;
			}
			fseek (fil, 0, SEEK_SET);
			if ( str <= 10){
				// вывести весь файл
				while(!feof (fil)) {
					if (fgets(s, 255, fil))
					printf("%s", s);
				}
			} else {
				str1 = str - 10;
				for (int i = 0; i < str1; i++){
					// пропустить str1 строк
					fgets(s, 255, fil);
				}
				// вывести все остальные
				while(!feof (fil)) {
					if (fgets(s, 255, fil))
					printf("%s", s);
				}
			}
			fclose(fil);
		}
	} else {
		printf("не удалось выполнить команду tail\n");
	}
	return;
}

//Функция перенаправляет стандартный поток ввода на вывод из файла
void change_in(Tree t){
    int fin;
    if ( (fin = open(t->infile, O_RDONLY )) == -1){
        printf("не удалось открыть файл %s\n", t->infile);
      } else {
        dup2(fin, 0);
        printf("перенаправил из файла %s\n", t->infile);
        close(fin);
      }
}

//Функция перенаправляет стандартный поток вывода на вывод в файл

void change_out(Tree t){
    int fout;
    fout = open(t->outfile, O_WRONLY|O_CREAT|O_TRUNC, 0666);
                  
    if (fout == -1)
      printf("не удалось открыть файл %s\n", t->outfile);
    else {
        dup2(fout, 1);
        fprintf(stderr, "перенаправил в файл %s\n", t->outfile);
        close(fout);
    }
}


//Функция удаления списка pid
void del_all_pid(pidlist p){
  if (p == NULL)
    return;
  del_all_pid(p->next);
  free(p);
}

//Функция печати списка pid
void print_pid(pidlist p){
    if (p == NULL) 
	    return;
    while (p != NULL){
        printf("%d\n",p->pid);
        p = p->next;
    }
}
  
//Функция добавления нового узла в список pid
void add_pid(pidlist * p, int elem){
    if (*p == NULL){
        if ( ( *p = malloc(sizeof(struct listforpid)) ) == NULL){
            printf("malloc: не выделяется память");
            return;
        }
        (*p)->pid = elem;
        (*p)->next = NULL;
		return ;
    } else
      add_pid(&(*p)->next, elem);
  }

//Функция удаления завершенных прцессов
void clear_zombie(pidlist *p){
    int pid;
    if (*p == NULL) {
	      return;
    }
    while (*p != NULL){
        if ( (pid = waitpid((*p)->pid, 0, WNOHANG)) != 0){ //означает немедленное возвращение управления, если ни один дочерний процесс не завершил выполнение.
            fprintf(stderr, "процесс %d завершился\n", pid);
            del_pid(p, pid);
            return ;
        }
        p = &(*p)->next;
   }
}
  
//Функция удаления процесса с определенным pid 
void del_pid(pidlist *p, int pid){
    pidlist q;
    while (*p){
      if ((*p)->pid == pid){
          q = (*p);
          *p = q->next;
          free(q);
          return ;
      } else
        p = &(*p)->next;
	}
	return ;
}
 
 /* 
int main(){
	Tree cmds;
	cmds->argv[0] = "cd";
	cmds->argv[1] = NULL;
	printf("%d", count_next(cmds));
	pidlist p1 = NULL;
	//exec_com(cmds, &p1);
	return 0;
}*/

/*
		if (strcmp(tree1->argv[0], "cd") == 0 ){
			//выполнение команды cd 
			exec_cd(tree1->argv);
            continue;
		}
		if (strcmp(tree1->argv[0], "pwd") == 0 ){
			//выполнение команды pwd 
			exec_pwd(tree1->argv);
            continue ;
		}
		if (strcmp(tree1->argv[0], "exit") == 0 ){
			//выполнение команды exit 
			exec_exit(tree1->argv);
            continue ;
		}
		if (strcmp(tree1->argv[0], "mv") == 0 ){
			//выполнение команды mv 
			exec_mv(tree1->argv);
            continue ;
		}
		if (strcmp(tree1->argv[0], "wc") == 0 ){
			//выполнение команды wc 
			exec_wc(tree1->argv);
            continue ;
		}
		if (strcmp(tree1->argv[0], "tail") == 0 ){
			//выполнение команды tail 
			exec_tail(tree1->argv);
            continue ;
		}*/
