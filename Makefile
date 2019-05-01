CC = gcc
CFLAGS = -g -Wall
OBJS = main.o util.o lex.yy.o cm.tab.o
TARGET = 20161616
OTHERS = lex.yy.c cm.tab.c cm.tab.h
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: globals.h util.h scan.h cm.tab.h parse.h main.c
	gcc $(CFLAGS) -c main.c

util.o: globals.h util.h util.c
	gcc $(CFLAGS) -c util.c

lex.yy.o: globals.h util.h scan.h lex.yy.c
	gcc $(CFLAGS) -c lex.yy.c
lex.yy.c: tiny.l
	flex tiny.l

cm.tab.c cm.tab.h : cm.y
	bison -dv cm.y

clean:
	rm -rf *.o $(TARGET) $(OTHERS)
