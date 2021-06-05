CC := clang
main.o:main.c
	$(CC) -o main.o -c main.c

exe: main.o
	$(CC) -o exe main.o -lm
