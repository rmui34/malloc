# malloc
// David Rennick , Raymond Mui
// CSE 374 Homework 6
// 3.5.15

Work Distribution:

	Raymond Mui:
	Most of Makefile
	Initial structure of most files, including most of header files
	freemem.c
	print_heap.c

	David Rennick:
	test and dist targets in Makefile
	getmem.c 
	get_mem_stats.c

	The initial concepts, and methods of operation, were planned out collaboratively.
	The implementation was divided between members and testing was done by each member as needed.



Heap and allocation design:

	Malloc is used to allocate new 4096 byte blocks as needed.

	The header of each block consists two uintptr_t sized sections.
	The first stores the size of the data section of the block.
	The second stores a pointer to the data section of the next block
	The remainder of the block is for the user's data.

	The list of free data functions as a singly linked list using the "next" section of the blocks
	to point to the next element of the list.

	Blocks are referred to using a pointer to their data sections, and all other values are
	calculated using get functions.


	 

Resources:

	The wikipedia page on dynamic memory allocation was used to get a basic understanding of structure
	and terminollogy for the project.
	http://en.wikipedia.org/wiki/C_dynamic_memory_allocation


