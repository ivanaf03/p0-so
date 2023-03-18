all: clean executable execute 

executable: p0.o lista.o
	gcc -Wall -o p0 p0.o lista.o

p0.o:
	gcc -c p0.c 

lista.o:
	gcc -c lista.c

execute: 
	./p0

valgrind: clean executable
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-report.txt ./p0

clean:
	rm -f *.o *.txt p0