CC=gcc
OBJ= parser.tab.o scanner.o main.o stmt.o decl.o expr.o type.o scope.o symbol.o hash_table.o 

all: stsh

stsh: $(OBJ)
	$(CC) $^ -o $@ -lm -g -O0

%.o: %.c %.h
	$(CC) -c $< -o $@ -lm -g -O0

scanner.c: scanner.flex parser.tab.h
	flex --outfile=$@ $^

parser.tab.c parser.tab.h: parser.y
	bison -d -bparser -v $^

.PHONY: clean

clean:
	rm -f *.o scanner.c parser.tab.* parser.output stsh
