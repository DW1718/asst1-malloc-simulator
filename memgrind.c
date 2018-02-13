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
	//if we run only 1 iteration we don't get any attempts to free a non existent address
	//but once we run more then 1 iteration we start to see attempts to free non existent
	//addresses, need to figure out why, I think it has something to do with the actual
	//memory being recycled but i'm not sure how to verify or solve this if this is the case
	//regardless, this testC function is the correct structure in which we need to run testC
	while(testCount<150){
		printf("Test C number %d...................................................\n", testCount);
		int i=0;
		int j=0;
		float r;
		//void* ptr;
		char *arr[150];
		int m;
		for(m=0; m<150; m++){
			arr[m] = NULL;
		}
		while(i<150&&j<150){
			r = (double)rand() / (double)RAND_MAX;
			if (r<.5){
				printf("Test C malloc...\n");
				arr[i] = malloc(1);
				i++;
				//printf("%d\n", i);
				printf("Test C malloc is successful!\n");
				continue;
			}
			else{
				//printf("Test C free...\n");
				int k;
				//output says we are trying to free a NULL pointer, how?
				for(k=0; k<150; k++){
					//printf("%d\n", k);
					if(arr[k]){
						free(arr[k]);
						arr[k]=NULL;
						printf("Test C free is successful\n");
						j++;
						break;
					}
					else
						continue;
				}
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
