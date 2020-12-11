a.out: main.o server.o
	gcc main.o server.o -Wall -Wextra -lpthread

main.o:
	gcc -c main.c -Wall -Wextra -lpthread

server.o:
	gcc -c server.c -Wall -Wextra -lpthread

run: a.out
	./a.out

clear:
	rm a.out main.o server.o
