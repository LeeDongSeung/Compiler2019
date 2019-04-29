CC = gcc
CFLAGS = -Wall
OBJS = main.o util.o lex.yy.o
TARGET = 20161616
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -lfl

main.o: globals.h util.h scan.h main.c
	gcc -Wall -c main.c

util.o: globals.h util.h util.c
	gcc -Wall -c util.c

lex.yy.o: globals.h util.h scan.h tiny.l
	flex tiny.l
	gcc -Wall -c lex.yy.c -lfl

clean:
	rm -rf *.o $(TARGET) lex.yy.c
