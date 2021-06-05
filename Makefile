main.o:main.c
	clang -o main.o -c main.c

exe: main.o
	clang -o exe main.o -lm