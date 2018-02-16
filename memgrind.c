/* memgrind.c source code to run our main and test our malloc and free functions*/
/*Your memgrind.c should run all the workloads, one after the other, 100 times.  It
should record the run time for each workload and store it.  When all 100 iterations
of all the workloads have been run, memgrind.c should calculate the mean time for
each workload to execute and output them in sequence.*/

//NEED TO FREE ALL MEMORY USED AFTER EACH TEST

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "mymalloc.h"


int getrand(int min,int max){
     return(rand()%(max-min)+min);
}

//malloc 1 byte and immediately free it, do this 150 times
void testA(){
		int i;
		for(i=0;i<150;i++){
			printf("Test A malloc\n");
			void* ptr = malloc(1);
			printf("Test A free\n");
			free(ptr);
		}
}

//malloc 1 byte, store the pointer in an array, do this 150 times
//Once you've malloced 150 byte chunks, free the 150 1 byte
//pointers one by one!
void testB(){
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
}

//Randomly choose between a 1 byte malloc() or free()ing a 1 byte pointer - do this 150 times
//Keep track of each operation so that you eventually malloc() 150 bytes, in total
//Keep track of each operation so that you eventually free() all pointers
//(don't allow a free() if you have no pointers to free())

void testC(){
	//RESOLVED(this is fine):
	//if we run only 1 iteration we don't get any attempts to free a non existent address
	//but once we run more then 1 iteration we start to see attempts to free non existent
	//addresses, need to figure out why, I think it has something to do with the actual
	//memory being recycled but i'm not sure how to verify or solve this if this is the case
	//regardless, this testC function is the correct structure in which we need to run testC
		int i=0;
		int j=0;
		float r;
		//void* ptr;
		char *arr[150];
		int m;
		for(m=0; m<150; m++){
			arr[m] = NULL;
		}

		while(i<150){
			r = (double)rand() / (double)RAND_MAX;
			if (r<.5){
				printf("Test C malloc...%d\n", i);
				arr[i] = malloc(1);
				i++;
				continue;
			}
			else{
				int k;
				//output says we are trying to free a NULL pointer, how?
				for(k=0; k<150; k++){
					if(arr[k]){
						printf("Test C free...\n");
						free(arr[k]);
						arr[k]=NULL;
						break;
					}
					else
						continue;
				}
			}
		}
		//clear the remaining array
		for(j=0; j<150; j++){
			free(arr[j]);
		}
}
/*Randomly choose between a randomly-sized malloc() or free()ing a pointer – do this many times (see below)

- Keep track of each malloc so that all mallocs do not exceed your total memory capacity

- Keep track of each operation so that you eventually malloc() 150 times

- Keep track of each operation so that you eventually free() all pointers

- Choose a random allocation size between 1 and 64 bytes
*/
void testD(){
	//test D is giving sensible outputs but is only getting through 6 iterations before
	//the program gets hung up, also facing the same problem of attempting to free
	//non existent addresses as in test C which I do not understand because the array
	//that I am storing the pointers in should only be holding pointers that we
	//initialized and assigned and I clear the locations of the array appropriately
	//every time we free a pointer
		int i=0;
		int j=0;
		int iter = 0;
		int memAlloc=0;
		int m;
		char* arr[150];
		float r;
		for(m=0; m<150; m++){
			arr[m]=NULL;
		}
		while(i<150){
			printf("Test D ITERATION NUMBER %d\n", iter);
			r = (double)rand()/ (double)RAND_MAX;
			int rand = getrand(1, 64);
			if(r<.5&&(memAlloc+rand)<=5000){
				printf("Test D malloc...\n");
				arr[i]=malloc(rand);
				if(arr[i]){
					printf("Test D malloc is successful!\n");
					memAlloc+=rand;
					i++;
				}
				continue;
			}
			else{
				int k;
				for(k=0; k<150; k++){
					if(arr[k]){
						free(arr[k]);
						arr[k]=NULL;
						printf("Test D free is successful!\n");
						break;
					}
					else{
						continue;
					}
				}
			}
			iter++;
		}
		for(j=0; j<150; j++){//free()ing all pointers in memory
			free(arr[j]);
		}
		printf("Total memory allocation in D was %d\n", memAlloc);

}

void testE(){
	return;
}

void testF(){
	return;
}

int main(){
	int total=0;
	int i;
	int j=0;
	int res[600];
	struct timeval start, end;

	for(i=0; i<100;i++){
		//testA
		gettimeofday(&start, NULL);
		testA();
		gettimeofday(&end, NULL);
		total=total+((end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec));
		res[j]=total;
		j++;

		//testB
		total=0;
		gettimeofday(&start, NULL);
		testB();
		gettimeofday(&end, NULL);
		total=total+((end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec));
		res[j]=total;
		j++;

		//testC
		total=0;
		gettimeofday(&start, NULL);
		testC();
		gettimeofday(&end, NULL);
		total=total+((end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec));
		res[j]=total;
		j++;

		/*testD
		total=0;
		gettimeofday(&start, NULL);
		testD();
		gettimeofday(&end, NULL);
		total=total+((end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec));
		char[j]=total;
		j++;*/

	}

	int k;
	int aRes=0;
	for(k=0;k<100;k++){
		aRes+=res[k];
	}
	printf("Test A average time is %d milliseconds\n", aRes/100);

	int bRes=0;
	for(k=100;k<200;k++){
		bRes+=res[k];
	}
	printf("Test B average time is %d milliseconds\n", bRes/100);

	int cRes=0;
	for(k=200;k<300;k++){
		cRes+=res[k];
	}
	printf("Test C average time is %d milliseconds\n", cRes/100);

	/*int dRes=0;
	for(k=300;k<400;k++){
		dRes+=res[k];
	}

	int eRes=0;
	for(k=400;k<500;k++){
		eRes+=res[k];
	}

	int fRes=0;
	for(k=500;k<600;k++){
		fRes+=res[k];
	}*/

	return 0;
}
