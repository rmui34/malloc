// David Rennick , Raymond Mui
// CSE 374 Homework 6
// 3.5.15
/*! freemem.c
 * This returns a block of storage that is passed and puts it back onto	 
 * the freelist. Will combine adjacent free blocks into a single block and place 
 * the combine block onto the freelist. 
 * 
 * Table of Contents
 * 1) void freemem(void* p)  - inserts the passed memory block back onto the free list
 * 2) void reinsert(void* p) - reinserts memory block
 * 3) void reinsertRec(void* p, void* node) -searches for a block of free memory and combines
 * 														fragmented blocks.
 *
 */

#include "mem_impl.h" // contains functions that get information about the memory block

void reinsert(void* p); 
void reinsertRec(void* p, void* node);

// Inserts the passed memory block back onto the free list
void freemem(void* p)	{
	if(p == NULL){
		return;
	}

	if((uintptr_t*)headData == NULL ){
		headData = (uintptr_t*)p;
	} else {
		reinsertRec(p, headData);
	}
}

// Inserts passed block back into free list recursively
void reinsertRec(void* p, void* node){
	// Insert if end of list found
	if(*(uintptr_t*)getNext(node) == (uintptr_t)NULL){
			*(uintptr_t*)getNext(node) = (uintptr_t)p;
			*(uintptr_t*)getNext(p) = (uintptr_t)NULL;
			return;
	 }
	// If insertion point found
	if((uintptr_t*)p < (uintptr_t*)*(uintptr_t*)getNext(node)) {
		// Insert node into list
 		*(uintptr_t*)getNext(p) = *(uintptr_t*)getNext(node);
		*(uintptr_t*)getNext(node) = (uintptr_t)p;
 		uintptr_t* nextNode = (uintptr_t*)*(uintptr_t*)getNext(p);
		// If possible combine with preceding node
		if((uintptr_t*)getEnd(node) == (uintptr_t*)getFront(p)) {
			*(uintptr_t*)getNext(node) =(uintptr_t)nextNode;
			*(uintptr_t*)getSize(node) = (uintptr_t*)getEnd(p) - (uintptr_t*)node;
			// If possible combine with following node
			if(nextNode != NULL && (uintptr_t*)getEnd(node) == (uintptr_t*)getFront(nextNode)) {
				*(uintptr_t*)getNext(node) =(uintptr_t)*(uintptr_t*)getNext(nextNode);
				*(uintptr_t*)getSize(node) = (uintptr_t*)getEnd(nextNode) - (uintptr_t*)node;
			}
			return;
		}

		// If possible combine with following node
		if(nextNode != NULL && (uintptr_t*)getEnd(p) == (uintptr_t*)getFront(nextNode)) {
			*(uintptr_t*)getNext(p) =(uintptr_t)*(uintptr_t*)getNext(nextNode);
			*(uintptr_t*)getSize(p) = (uintptr_t*)getEnd(nextNode) - (uintptr_t*)p;
		}	
	} else { // Continue searching list for insertion point
		reinsertRec( p, (uintptr_t*)*(uintptr_t*)getNext(node) );
	}
}

