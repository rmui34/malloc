#!/bin/bash
# David Rennick, Raymond Mui
# CSE 374 Homework 6
# 3.5.15


bench: getmem.o freemem.o get_mem_stats.o print_heap.o bench.o
	gcc -std=c99 -Wall -g -o bench bench.o getmem.o freemem.o get_mem_stats.o print_heap.o 

bench.o: bench.c  mem.h
	gcc -std=c99 -Wall -g -c bench.c

getmem.o: getmem.c mem_impl.h
	gcc -std=c99 -Wall -g -c getmem.c

freemem.o: freemem.c mem_impl.h
	gcc -std=c99 -Wall -g -c freemem.c

get_mem_stats.o: get_mem_stats.c mem_impl.h
	gcc -std=c99 -Wall -g -c get_mem_stats.c

print_heap.o: print_heap.c mem_impl.h
	gcc -std=c99 -Wall -g -c print_heap.c

test: bench
	./bench

dist: bench
	git log > ./git.log
	git ls-files > ./git.list
	tar cf hw6.tar ./*.c ./*.h ./README ./git.log ./git.list ./Makefile

clean:
	rm -f *.o
	rm -f *~
	rm -f git.log
	rm -f git.list
	rm -f hw6.tar
	rm -f bench









