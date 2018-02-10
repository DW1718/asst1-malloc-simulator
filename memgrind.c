/* memgrind.c source code to run our main and test our malloc and free functions*/
/*Your memgrind.c should run all the workloads, one after the other, 100 times.  It
should record the run time for each workload and store it.  When all 100 iterations
of all the workloads have been run, memgrind.c should calculate the mean time for
each workload to execute and output them in sequence.*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "mymalloc.h"

//malloc 1 byte and immediately free it, do this 150 times
void testA(){
	int testCount=0;
	while(testCount<150){
		int i;
		for(i=0;i<150;i++){
			void* ptr = malloc(1);
			free(ptr);
		}
		testCount++;
	}
}

//malloc 1 byte, store the pointer in an array, do this 150 times
//Once you've malloced 150 byte chunks, free the 150 1 byte
//pointers one by one!
void testB(){
	int testCount=0;
	while(testCount<150){
		int i;
		char* arr[150];
		for(i=0;i<150;i++){
			arr[i]=malloc(1);
		}
		for(i=0;i<150;i++){
			free(arr[i]);
		}
		testCount++;
	}
}

//Randomly choose between a 1 byte malloc() or free()ing a 1 byte pointer - do this 150 times
//Keep track of each operation so that you eventually malloc() 150 bytes, in total
//Keep track of each operation so that you eventually free() all pointers
//(don't allow a free() if you have no pointers to free())

void testC(){
	printf("\n\nTEST C\n\n");
	int testCount=0;
	while(testCount<150){
		int i;
		float r;
		void* ptr;
		for(i=0;i<150;i++){
			r = (double)rand() / (double)RAND_MAX;
			if (r<.5){
				ptr = malloc(1);
			}
			else{
				free(ptr);
			}
		}
		testCount++;
	}
}

int main(){
	testA();
	testB();
	testC();
    return 0;
}
