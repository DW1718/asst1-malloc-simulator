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
		printf("Test A number %d...................................................\n", testCount);
		int i;
		for(i=0;i<150;i++){
			printf("Test A malloc\n");
			void* ptr = malloc(1);
			printf("Test A free\n");
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
		printf("Test B number %d...................................................\n", testCount);
		int i;
		char* arr[150];
		for(i=0;i<150;i++){
			printf("Test B malloc\n");
			arr[i]=malloc(1);
		}
		for(i=0;i<150;i++){
			printf("Test B free\n");
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
	int testCount=0;
	while(testCount<150){
		printf("Test C number %d...................................................\n", testCount);
		int i;
		float r;
		void* ptr;
		for(i=0;i<150;i++){
			r = (double)rand() / (double)RAND_MAX;
			if (r<.5){
				printf("Test C malloc\n");
				ptr = malloc(1);
			}
			else{
				printf("Test C free\n");
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
