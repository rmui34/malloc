// David Rennick , Raymond Mui
// CSE 374 Homework 6
// 3.5.15
/*! print_heap.c
 * 
 * Prints the state of the free list to a file stream
 *
 */

#include "mem_impl.h"
#include <stdio.h>

// Prints the head address and data section value of all blocks on the free list in HEX to FILE * f
void print_heap(FILE * f)	{
	void* curr = headData;
	while( curr != NULL ) {
		fprintf(f, "0x%016lx 0x%016lx\n", (unsigned long)(uintptr_t*)getFront(curr), (unsigned long)*(uintptr_t*)getSize(curr));
		curr = (uintptr_t*)*(uintptr_t*)getNext(curr);
	}
}

