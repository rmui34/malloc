// David Rennick , Raymond Mui
// CSE 374 Homework 6
// 3.5.15
/*! get_mem_stats.c
 *
 * Sets the passed pointer locations to values of the free list status.
 *
 */

#include "mem_impl.h"

/*
* Sets the values in the passed pointers based on the current state of the memory heap.
* total_size: Total size in bytes allocated for the memory heap
* total_free: Total size in bytes of blocks in free list including headers
* n_free_blocks: Number of free blocks in the free list
*/
void get_mem_stats(uintptr_t* total_size, uintptr_t* total_free, uintptr_t* n_free_blocks) {
	*total_size = mallocCount * BLOCKSIZE;
	*total_free = 0;
	*n_free_blocks = 0;

	void* curr = headData;

	while( curr != NULL ) {
		*total_free += 16 + (uintptr_t)*(uintptr_t*)getSize(curr)/8;
		*n_free_blocks+=1;
		curr = (uintptr_t*)*(uintptr_t*)getNext(curr);
	}
}
