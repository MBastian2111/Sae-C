main.o:main.c fonction.h
	gcc -g -c main.c
fonction.o:fonction.c fonction.h
	gcc -g -c fonction.c
all:main.o fonction.o
	gcc -g main.o fonction.o -o annuairedecmorts