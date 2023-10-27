CC = gcc

main:
	$(CC) -o main my_functions.c main.c

tests:
	$(CC) -o tests my_functions.c test.c

run:
	make clean
	make main
	./main

test:
	make tests
	./tests

clean:
	rm -f main
	rm -f tests
	clear