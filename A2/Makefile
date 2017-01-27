OBJQ1 = linkedList.o q1.o io.o functions.o sort.o
OBJQ2 = q2.o
FLAGS = -Wall -std=c99 -Iinclude
EXE = run

q2: $(OBJQ2) q2.o
	gcc $(OBJQ2) -o q2 $(FLAGS)
q1: $(OBJQ1) 
	gcc $(OBJQ1) -o q1 $(FLAGS)



cleanq1:
	rm $(OBJQ1) q1

main.o: src/main.c
	gcc -c src/main.c $(FLAGS)

linkedList.o: src/linkedList.c
	gcc -c src/linkedList.c $(FLAGS)

q1.o: src/q1.c
	gcc -c src/q1.c $(FLAGS)
q2.o: src/q2.c
	gcc -c src/q2.c $(FLAGS)
io.o: src/io.c
	gcc -c src/io.c $(FLAGS)
functions.o: src/functions.c
	gcc -c src/functions.c $(FLAGS)
sort.o: src/sort.c
	gcc -c src/sort.c $(FLAGS)

