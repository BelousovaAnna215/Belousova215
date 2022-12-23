PROG = shell
CC = gcc
CFLAGS = -g -Wall

all:trytask35.o make_tree.o exec.o $(PROG)

trytask35.o: trytask35.c task35.h
	$(CC) $(CFLAGS) -c $< -o $@
make_tree.o: make_tree.c make_tree.h trytask35.o 
	$(CC) $(CFLAGS) -c $< -o $@
exec.o: exec.c exec.h make_tree.o
	$(CC) $(CFLAGS) -c $< -o $@
$(PROG): mymain.c trytask35.o make_tree.o exec.o 
	$(CC) $(CFLAGS) mymain.c trytask35.o make_tree.o exec.o -o $(PROG)
clean:
	rm -f *.o $(PROG)
run:
	./$(PROG)
