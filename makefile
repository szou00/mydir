all: dir.o
	gcc -o a.out dir.o

main.o: dir.c
	gcc -c dir.c

run:
	./a.out

clean:
	rm *.o
	rm *~
