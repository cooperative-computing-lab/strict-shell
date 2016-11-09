CC=gcc
OBJ= parser.tab.o scanner.o main.o stmt.o decl.o expr.o type.o 

all: stsh

stsh: $(OBJ)
	$(CC) $^ -o $@

%.o: %.c %.h
	$(CC) -c $< -o $@

scanner.c: scanner.flex parser.tab.h
	flex --outfile=$@ $^

parser.tab.c parser.tab.h: parser.y
	bison -d -bparser -v $^

.PHONY: clean

clean:
	rm -f *.o scanner.c parser.tab.* parser.output stsh
