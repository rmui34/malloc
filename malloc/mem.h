// David Rennick , Raymond Mui
// CSE 374 Homework 6
// 3.5.15
/*! mem.h
 *
 * Header file for public interface function prototypes
 *
 */

#include<stdio.h>
#include<inttypes.h>

#ifndef MEM_H
#define MEM_H

// Allocates a block of size bytes of data and returns a pointer to its address
void* getmem(uintptr_t size);

// Returns the passed allocated block to the free list.
// p must be an allocated block, and should only be called once on each block
void freemem(void* p); 

/*
* Sets the values in the passed pointers based on the current state of the memory heap.
* total_size: Total size allocated for the memory heap
* total_free: Total size in bytes of blocks in free list including headers
* n_free_blocks: Number of free blocks in the free list
*/
void get_mem_stats(uintptr_t* total_size, uintptr_t* total_free, uintptr_t* n_free_blocks); 

// Prints the head address and data section size of all blocks on the free list in HEX to FILE * f
void print_heap(FILE * f);

#endif //MEM_H

