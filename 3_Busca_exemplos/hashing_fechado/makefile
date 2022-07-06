all: main.o 
	gcc main.o -o execute -pedantic-errors -Wall -lm; ./execute

main.o:
	gcc -c main.c -o main.o

run:
	./execute

clean:
	rm *.o *.zip execute; clear