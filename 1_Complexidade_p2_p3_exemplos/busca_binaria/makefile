all: lista.o main.o 
	gcc lista.o main.o -o execute -pedantic-errors -Wall -lm; ./execute

lista.o:
	gcc -c lista.c -o lista.o

main.o:
	gcc -c main.c -o main.o

run:
	./execute

clean:
	rm *.o *.zip execute