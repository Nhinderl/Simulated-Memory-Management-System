CC=gcc
CFLAGS=-Wall -ansi -g -pedantic

all: src/ds_memory.o src/ds_array.o src/ds_list.o src/main.o

array: src/ds_memory.o src/ds_array.o src/main.o
	$(CC) $(CFLAGS) src/ds_memory.o src/ds_array.o src/main.c -o runArray

list: src/ds_list.o src/ds_memory.o src/main.o
	$(CC) $(CFLAGS) src/ds_list.o src/ds_memory.o src/main.c -o runList

main.o: src/main.c src/ds_memory.c src/ds_list.c src/ds_list.h src/ds_array.c src/ds_memory.h src/ds_array.h
	$(CC) $(CFLAGS) src/ds_array.c src/ds_memory.c src/ds_list.c src/main.c -o main.o

ds_memory.o: src/ds_memory.c src/ds_memory.h 
	$(CC) $(CFLAGS) src/ds_memory.c -o ds_memory.o

ds_array.o: src/ds_array.c src/ds_array.h src/ds_memory.h src/ds_memory.c
	$(CC) $(CFLAGS) src/ds_array.c src/ds_memory.c -o ds_array.o

ds_list.o: src/ds_memory.h src/ds_list.c src/ds_list.h src/ds_memory.c
	$(CC) $(CFLAGS) src/ds_list.c src/ds_memory.c -o ds_list.o
