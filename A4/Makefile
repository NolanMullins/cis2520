OBJQ1 = main.o extra.o io.o tree.o
FLAGS = -Wall -std=c99 -Iinclude
EXE = avltree


all:$(OBJQ1) 
	gcc $(OBJQ1) -o $(EXE) $(FLAGS)
clean:
	rm $(OBJQ1) $(OBJQ2) $(EXE)
run:
	./avltree

main.o: src/main.c
	gcc -c src/main.c $(FLAGS)
extra.o: src/extra.c include/extra.h
	gcc -c src/extra.c $(FLAGS)
io.o: src/io.c include/io.h
	gcc -c src/io.c $(FLAGS)
tree.o:	src/tree.c include/tree.h
	gcc -c src/tree.c $(FLAGS)
