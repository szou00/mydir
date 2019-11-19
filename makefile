all: dir.o
	gcc -o program dir.o

main.o: dir.c
	gcc -c dir.c

run:
	./program

clean:
	rm *.o
	rm *~
