OBJQ1 = q1.o extra.o io.o tree.o
OBJQ2 = q2.o io.o nameThisLater.o
FLAGS = -Wall -std=c99 -Iinclude
EXE = run


all:q1 q2

q1: $(OBJQ1) 
	gcc $(OBJQ1) -o q1 $(FLAGS)
q2: $(OBJQ2)
	gcc $(OBJQ2) -o q2 $(FLAGS)

test1:
	./q1 "(((1+2)+(2+4))+(2-1))"
test2:
	./q1 '(x1/(1.0+1.0))'
test3:
	./q1 '(((x1/(2.0+2.0))+((2.0+1.0)*(3.6-0.6)))+(((3.6-0.6)-(3.6-0.6))+((3.6-0.6)-(3.6-0.6))))'
test4:
	./q1 '(((1.0+1.0)/x1))'
test5:
	./q1 '(x1/(1.0+(1.0+(1.0+1.0))))'
test6:
	./q1 '(x1/0)'

clean:
	rm $(OBJQ1) $(OBJQ2) q1 q2

q1.o: src/q1.c
	gcc -c src/q1.c $(FLAGS)
q2.o: src/q2.c
	gcc -c src/q2.c $(FLAGS)
extra.o: src/extra.c include/extra.h
	gcc -c src/extra.c $(FLAGS)
io.o: src/io.c include/io.h
	gcc -c src/io.c $(FLAGS)
tree.o:	src/tree.c include/tree.h
	gcc -c src/tree.c $(FLAGS)
nameThisLater.o: src/nameThisLater.c include/nameThisLater.h
	gcc -c src/nameThisLater.c $(FLAGS)