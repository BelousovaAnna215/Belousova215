#include "task35.h"

typedef char ** list;

int c; //текущий символ 
char * buf; // буфер для накопления текущего слова
int sizebuf; // размер буфера текущего слова
int sizelist;// размер списка слов
int curbuf; // индекс текущего символа в буфере
int curlist; // индекс текущего слова в списке

char getsym1();
char getsym();
void start();
void word();
void greater();
void amper();
void stick();
void doub();
void quotes();
void newline();
void stop();

void clearlist(list * array_str);
void null_list();
void termlist();
void nullbuf();
void addsym();
void addword();
void printlist(char ** array_str);
int symset(int c);
void sortlist();

//  функция считывает по очереди все элементы со стандартного потока ввода, используя буффер в N элементов
char getsym1(){
	static char symbols[N]= {'a'};
	static int i = N+1;
	if ( i >= N ){
		// Устанавливаем в буфере 0
		for (int k = 0;k != N;k++){
			symbols[k] = '\0';
		}
		if (fscanf( stdin, "%10c", symbols) == EOF){
			printf("EOF\n");
			exit(0);
		}
		if (symbols[0] == '\0'){
			i = N + 1;
			return getsym1(); // !!!!!
		} else {
			i = 1;
			return symbols[0];
		}
	} else {
		if (symbols[i] == '\0'){
			i = N + 1;
			return getsym1(); // !!!!!!
		} else {
			i++;
			return symbols[i - 1];
		}
	}
}

char getsym(){
	return getchar();
}


void start() {
	//printf("start\n");
	if (c == ' '|| c == '\t'){
		//printf("c = ' '\n");
		c = getsym();
		start();
	} else if (c == EOF){
		//printf("c = EOF\n");
		termlist();
		//printlist();
		//clearlist();
		//stop();
		exit(0);
	} else if (c == '\n'){
		termlist();
		//printlist();
		//sort
		//sortlist();
		//printlist();
		//c = getsym();
		//newline();
		stop();
	} else if (c == '"'){
		c = getsym();
		nullbuf(); // !!!
		quotes();
	} else { 
		int newc = c;
		//printf("newc = %d\n", c);
		nullbuf();
		addsym();
		c = getsym();
		//printf("c = %d\n", c);
		switch( newc ){
			case '>':
				greater();
				break;
			case '<' :
				doub();
				break;
			case '|' :
				stick();
				break;
			case '&':
				amper();
				break;
			case '(' :
				doub();
				break;
			case ')' :
				doub();
				break;
			case ';' :
				doub();
				break;
			default:
				word();
				break;
		}
	}
}

void word(){
	//printf("word\n");
	if( symset(c) ) {
		addsym();
		c = getsym();
		//printf("%d\n", c);
		word();
	} else {
		//printf("+word\n");
		addword();
		start();
	}
}

//>
void greater() { 
	if(c == '>') {
		addsym();
		c = getsym();
		doub();
	} else {
		addword();
		start();
	}
}

// обработка двойных и некотторых одиночных символов
void doub() {
	addword();
	start();
}

// обработка кавычек
void quotes(){
	if (c == '\n'){
		printf("error");
		termlist();
		c = getsym();
		//newline();
		stop();
	}
	if (c == EOF){
		printf("error");
		termlist();
		//printlist();
		clearlist(&array_str);
		stop();
	}
	//printf("quotes\n");
	if (c != '"'){
		addsym();
		c = getsym();
		quotes();
	} else {
		c = getsym();
		//printf("quotes1\n");
		addword();
		start();
	}
}	


//&
void amper() { 
	if(c == '&') {
		addsym();
		c = getsym();
		doub();
	} else {
		addword();
		start();
	}
}



// |
void stick() { 
	if(c == '|') {
		addsym();
		c = getsym();
		doub();
	} else {
		addword();
		start();
	}
}



//void newline(){
	//printf("newline\n");
	//clearlist();
	// start();
//	return;
 //}


void stop(){
	//printf("end\n");
	//exit(0);
	return;
} 

// функция очистки памяти
void clearlist(list * array_str){
	//printf("clearlist\n");
	int i;
	if (*array_str == NULL) 
		return;
	for (i=0; *(*array_str+i) != NULL; i++)
		free (*(*array_str + i));
	free (*array_str);
	*array_str = NULL;
}


// функция обнуления списка(создания)
void null_list(){
	//printf("null_list\n");
	sizelist = 0;
	curlist = 0;
	array_str = NULL;
}

//Функция termlist() завершает список, добавляя NULL в позицию curlist и обрезает память, занимаемую списком, до точного размера.
void termlist(){
	//printf("termlist\n");
	if (array_str == NULL) 
		return;
	if ( curlist > sizelist-1 )
		array_str = realloc (array_str, ( sizelist + 1 )*sizeof(*array_str));
	array_str[ curlist ] = NULL;
	array_str = realloc( array_str, ( sizelist = curlist + 1)*sizeof( *array_str ));//выравниваем используемую под список память точно по размеру списка
}

// обнуление buf
void nullbuf(){
	//printf("nullbuf\n");
	buf = NULL;
	sizebuf = 0;
	curbuf = 0;
}


//Функция добавляет очередной символ в буфер. Если буфер был пуст, то он создается.
void addsym(){
	//printf("addsym\n");
	if ( curbuf > sizebuf - 1 )
		buf = realloc( buf, sizebuf += SIZE); // увеличиваем буфер при необходимости 
	buf [curbuf++] = c;
	//printf("add sym: %s\n",buf);
}

//Функция завершает текущее слово в буфере, добавляя ’\0’ и обрезает память до точного
//размера; Если список был пуст, то он создается.
void addword(){
	//printf("addword\n");
	if ( curbuf > sizebuf - 1)
		buf = realloc( buf, sizebuf += 1); // для записи ’\0’ увеличиваем буфер при необходимости 
	buf[ curbuf++ ]='\0';
	buf = realloc( buf, sizebuf = curbuf );//выравниваем используемую память точно по размеру слова
	if ( curlist > sizelist - 1 )
		array_str = realloc( array_str, ( sizelist += SIZE )*sizeof(*array_str)); // увеличиваем массив под список при необходимости 
	array_str[ curlist++ ] = buf;
	//printf("add word: %s\n",buf);
}

// функция печати списка
void printlist(list array_str){
	//printf("printlist\n");
	int i;
	if ( array_str == NULL)
		return;
	//printf("%d\n", sizelist - 1);
	for (i=0; array_str[i] != NULL; i++)
		printf( "%s\n", array_str[i] );
}

// функция возвращает 1 если обычный символ (не специальный)
int symset ( int c ){
	//printf("symset\n");
	return c != '\n' &&
	c != ' ' &&
	c != '|' &&
	c != '&' &&
	c != ';' &&
	c != '<' &&
	c != '(' &&
	c != ')' &&
	c != '\t' &&
	c != '>' &&
	c != EOF ;
} 


// функция упорядочивает список в лексикографическом порядке
void sortlist (){
	if (array_str == NULL)
		return;
	char *sortbuf = NULL;
	// bubble sort
	for (int i = 0; i < sizelist - 2; i++)
	{
		for (int j = 0; j < sizelist - i - 2; j++){ 
			if (strcmp(array_str[j], array_str[j+1]) > 0){
				sortbuf = array_str[j];
				array_str[j] = array_str[j+1];
				array_str[j+1] = sortbuf;
			}
		}
	}	
}

//функция заменяет строки специального вида на их значение
//$HOME (домашняя директория пользователя),
//$SHELL (путь к исполняемому в данный момент шеллу),
//$USER (имя пользователя, запустившего процесс),
//$EUID (идентификатор пользователя, с правами которого работает процесс).
void change (list array_str){
	#define PATH_MAX 255
	#define NAME_MAX 255
	#define ID_MAX 10
	char str_id[ID_MAX];
	int i;
	
	if (array_str == NULL)
		return;
		
	for (i=0; array_str[i] != NULL; i++){
		if (strcmp(array_str[i], "$HOME") == 0){
			free(array_str[i]);
            array_str[i] = malloc(PATH_MAX*sizeof(char));
            strcpy(array_str[i], getenv("HOME"));
		}
		if (strcmp(array_str[i], "$SHELL") == 0){
			free(array_str[i]);
            array_str[i] = malloc(PATH_MAX*sizeof(char));
            strcpy(array_str[i], getenv("PWD")); 
		}
		if (strcmp(array_str[i], "$USER") == 0){
			free(array_str[i]);
            array_str[i] = malloc(NAME_MAX*sizeof(char));
            strcpy(array_str[i], getlogin());
		}
		if (strcmp(array_str[i], "$EUID") == 0){
			sprintf(str_id, "%d", geteuid()); //вывод производится в массив str_id
            free(array_str[i]);
            array_str[i] = malloc(ID_MAX*sizeof(char));
            strcpy(array_str[i], str_id);
		}
	}
}

// функция строит список array_str 
char ** build_array(){
	c = getsym();
	//printf("%d\n", c);
	null_list();
	start();
	return array_str;
}
/*
int main(){
	char ** lst;
		lst = build_array();
		printlist(lst);
	return 0;
}
*/
