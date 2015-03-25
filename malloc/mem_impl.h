// David Rennick , Raymond Mui
// CSE 374 Homework 6
// 3.5.15
/*! mem_impl.h
 * This file allows for simple and safe integration of mem files.
 * Contains functions and variables to help integrate the memory
 * functions. 
 *
 */

#include<stdlib.h>
#include<inttypes.h>

#ifndef MEM_IMPL_H
#define MEM_IMPL_H

#define THRESHOLD 64 //Min bytes remaining for split
#define BLOCKSIZE 4096 //Size of blocks acquired by malloc


extern void* headData; //Head of free block list
extern int mallocCount; // Count of blocks acquired by malloc

// The following functions return pointers to the specific sections
// of memory blocks
// void* p should be the data section of the memory block

// Returns address front of header
void* getFront( void* p );

// Returns address size data
void* getSize( void* p );

// Returns address of bit beyond data
void* getEnd( void* p );

// Return address of next block's data
// Only valid for blocks on free list
void* getNext( void* p );

#endif //MEM_IMPL_H
