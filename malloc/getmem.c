// David Rennick , Raymond Mui
// CSE 374 Homework 6
// 3.5.15
/*! getmem.c
 *
 * Allocates a piece of memory at least the size requested.
 *
 */

#include "mem_impl.h"

// Prototypes
void* findFree( uintptr_t size );
int getNew( uintptr_t size );
void splitBlock( void* p, uintptr_t size );

void insert( void* p );
void insertRec( void* p, void* node );

void removeBlock(void* p);

// externed in mem_impl.h
void* headData = NULL; //Head of free block list
int mallocCount = 0; // Count of blocks acquired by malloc

// Allocates memory of requested size for user, and returns a pointer to its data region
void* getmem(uintptr_t size) {

	if(size <= 0 ){
		return NULL;
	}

	//Shift size to next multiple of 16
	if(size % 16){
		size = ((size / 16) * 16 ) + 16;
	}
	// Attempt to find block large enough
	void* tmpBlock = findFree( size );	
	// Allocate new block if large enough block not found
	if(tmpBlock == NULL){
		if(getNew( size ) == -1){
			return NULL;
		}
		// Find newly allocated block
		tmpBlock = findFree( size );
	}
	// Split block if reasonable
	splitBlock( tmpBlock, size );
	// Remove from free list
	removeBlock(tmpBlock);

	return tmpBlock;
}

// Finds a free contiguous block at least (size + header)
void* findFree( uintptr_t size ) {
	void* curr = headData;
	while( curr != NULL ) {
		if( *((uintptr_t*)getSize(curr)) >= size ) {
			return curr;
		}
		curr = (uintptr_t*)*(uintptr_t*)getNext(curr);
	}
	
	return NULL;
}

// Allocates new block and adds it onto free list
// Returns -1 if unable to allocate block
int getNew( uintptr_t size ) {
	void* newBlock;

	uintptr_t numBlocks = (size/BLOCKSIZE) + 1; // Number of blocks to allocate using malloc
	uintptr_t getNumber = BLOCKSIZE*numBlocks;

	newBlock = malloc(getNumber*8);

	if(newBlock == NULL){
		return -1;
	}
	mallocCount++;

	// Set new block's values
	newBlock = (uintptr_t*)newBlock + 2*sizeof(uintptr_t);
	*(uintptr_t*)getSize(newBlock) = (uintptr_t)getNumber - 2*sizeof(uintptr_t);
	*(uintptr_t*)getNext(newBlock) = 0;

	//Insert into list
	insert( newBlock );

	return 1;
}

// Splits block if enough excess data is graeter than THRESHOLD
void splitBlock( void* p, uintptr_t size ){

	uintptr_t pSize = *(uintptr_t*)getSize(p);
	if( (size + THRESHOLD) < pSize ){
		void* newBlock = (uintptr_t*)p + (uintptr_t)size + 2*sizeof(uintptr_t);
		getFront(newBlock);
		// set newBlock size
		*(uintptr_t*)getSize(newBlock) = ((uintptr_t*)getEnd(p) - (uintptr_t*)newBlock);
		// set newBlock next
		*(uintptr_t*)getNext(newBlock) = *(uintptr_t*)getNext(p);
		// set p size
		*(uintptr_t*)getSize(p) = size;
		// set p next
		*(uintptr_t*)getNext(p) = (uintptr_t)newBlock;
	}
}

// ** For the following void* p is the pointer to a block's data **

// Returns pointer to front of block
void* getFront( void* p ){
	return (uintptr_t*)p - 2*sizeof(uintptr_t);
}

// Returns pointer to block's size value
void* getSize( void* p ){
	return getFront( p );
}

// Returns a pointer to the address just beyond the block
void* getEnd( void* p ){
	return (uintptr_t*)p + (uintptr_t)*(uintptr_t*)getSize(p);
}

// Returns a pointer to a block's next block value
void* getNext( void* p ){
	return p - sizeof(uintptr_t);
}

// Insert block into list
void insert( void* p ){
	if ((uintptr_t*)headData == NULL){
		headData = (uintptr_t*)p;
	} else {
		insertRec( p, headData );
	}
}

// Recursive method for inserting block into list
// Call using insert helper function above
void insertRec( void* p, void* node ){
	// Insert if end of list found
	if(*(uintptr_t*)getNext(node) == (uintptr_t)NULL){
			*(uintptr_t*)getNext(node) = (uintptr_t)p;
			return;
	 }

	if ((uintptr_t*)p < (uintptr_t*)*(uintptr_t*)getNext(node)) {
		//point p->next to node->next
		*(uintptr_t*)getNext(p) = *(uintptr_t*)getNext(node);
		// point node->next to p
		*(uintptr_t*)getNext(node) = (uintptr_t)p;
	} else {
		// Continue searching for insert point
		insertRec( p, (uintptr_t*)*(uintptr_t*)getNext(node) );
	}
}

void removeBlock(void* p){
	void* curr = headData;
	// If head, remove head
	if( p == curr){
		headData = (uintptr_t*)*(uintptr_t*)getNext(curr);
		return;
	}

	//Find block
	while( (uintptr_t*)*(uintptr_t*)getNext(curr) != (uintptr_t*)p ) {
		curr = (uintptr_t*)*(uintptr_t*)getNext(curr);
	}
	// Remove
	*(uintptr_t*)getNext(curr) = *(uintptr_t*)getNext(p);
}

