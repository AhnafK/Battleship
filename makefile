all: testboard.c
	gcc testboard.c

run: a.out
	./a.out

clean: a.out
	rm a.out

debug: a.out
	rm a.out
	gcc -g testboard.c
	gdb ./a.out
