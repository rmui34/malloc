// David Rennick , Raymond Mui
// CSE 374 Homework 6
// 3.5.15
/*! bench.c
 *
 * Runs multiple get and free commands of using mem.h header with multiple
 * arguments to modify the behavior.
 * 
 * Argument format:
 * bench [ntrials [pctget [pctlarge [small_limit [large_limit [random_seed]]]]]]
 * command: descriptions (default value) (range)
 * ntrials: Total number of get or free commands (10000)(>0)
 * pctget:  Percentage of command that are get (50) (0-100%)
 * pctlarge: Percentage of commands that will be large sized blocks (10) (0-100%)
 * small_limit: Max size of small allocations (200) (<large_limit)
 * large_limit: Max size of large allocations. Must be larger than small_limit. (20000) (>small_limit)
 * random_seed: Specify a custom value for the random seed (Clock based seed) (>0)
 *  
 */

#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void printOut(unsigned int startTime, int percent);

int main(int argc, char** argv) {

	// Default argument values
	int ntrials = 10000;
	int pctget = 50;
	int pctlarge = 10;
	int small_limit = 200;
	int large_limit = 20000;
	unsigned int random_seed = (unsigned int)time(NULL);

	// Get arguments 
	if( argc > 1 ){
		ntrials = atoi(argv[1]);
		if( ntrials == 0 ){
			printf("Number of trials must be an integer greater than 0\n");
			return 1;
		}
	}
	if( argc > 2 ){
		pctget = atoi(argv[2]);
		if( pctget == 0 || pctget > 100 ){
			printf("percentage of get calls must be an integer from 1 to 100\n");
			return 1;
		}
	}
	if( argc > 3 ){
		pctlarge = atoi(argv[3]);
		if( (pctlarge == 0 && argv[3][0] != '0') || pctlarge > 100 || pctlarge < 0 ){
			printf("Percentage of large calls must be an integer from 0 to 100\n");
			return 1;
		} 
	}
	if( argc > 4 ){
		small_limit = atoi(argv[4]);
		if( small_limit <= 0 ){
			printf("The maximum size of small blocks must be an integer greater than 0\n");
			return 1;
		}
	}
	if( argc > 5 ){
		large_limit = atoi(argv[5]);
		if( large_limit <= 1 ){
			printf("The maximum size of large blocks must be an integer greater than 1\n");
			return 1;
		}
	}
	if( argc > 6 ){
		random_seed = strtoul(argv[6], NULL, 10);
		if( random_seed <= 0 ){
			printf("The random seed should be an integer greater than 0\n");
			return 1;
		}
	}
	if( argc > 7 ){
		printf("Too many arguments supplied to %s\n", argv[0]);
		return 1;
	}

	//Verify small is less than large
	if( small_limit >= large_limit ){
		printf("The small block size must be smaller than the large block size (large_limit: %d)\n", large_limit);
		return 1;
	}

	srand(random_seed);

	//Allocate array large enough to hold ntrials
	uintptr_t* memArray = (uintptr_t *)malloc(sizeof(uintptr_t) * ntrials);
	int used = 0;
	
	//run test
	unsigned int startTime = clock();
	int trialCount = 0; // Current trial
	int subCount = 0; // Count within each 10%
	
	int tenPerc = ntrials / 10; // trials per 10%
	int tenCount = 0; // tracks percentage complete

	int choice = 0; // get or free
	int sizeChoice = 0; // small or large

	int usedChoice = 0; // allocated item to free

	while( trialCount < ntrials ){
		while( (subCount < tenPerc || tenPerc == 0) && trialCount < ntrials) {
			// decide on command
			choice = rand() % 100 + 1;
			if( choice <= pctget ){
				// getmem
				choice = rand() % 100 + 1;
				if( choice > pctlarge ){
					sizeChoice = rand() % small_limit + 1;
				} else {
					sizeChoice = rand() % (large_limit - small_limit) + 1;
				}
				memArray[used] = (uintptr_t)getmem(sizeChoice);
				if( memArray[used] == (uintptr_t)NULL ){
					printf("Memory allocation failed! Closing Program.\n");
					return 1;
				}
				used++;
			} else {
				// freemem
				if( used > 0 ){
					usedChoice = rand() % used;
					freemem((uintptr_t*)memArray[usedChoice]);
					
					if(usedChoice != (used-1)){
						memArray[usedChoice] = memArray[used-1];
					}		
					used--;
				}
			}
			subCount++;
			trialCount++;
		}
		subCount = 0;
		tenCount++;

		if(tenCount < 10 && tenPerc != 0){ // Avoid printing status if ntrials < 10
			printOut( startTime, 10*tenCount );
		}
	}
	// Print final status for all sizes of ntrials
	printOut( startTime, 10*10 );

	return 0;
}


void printOut(unsigned int startTime, int percent){
	uintptr_t total_size = 0;
	uintptr_t total_free = 0;
	uintptr_t n_free_blocks = 0;
	get_mem_stats(&total_size, &total_free, &n_free_blocks);
	printf("%fs %%%i: ", (clock() - startTime)/(double)CLOCKS_PER_SEC, percent);
	printf("total_size: %d, total_free: %d, n_free_blocks: %d\n", (unsigned int)total_size, (unsigned int)total_free, (unsigned int)n_free_blocks);
}
