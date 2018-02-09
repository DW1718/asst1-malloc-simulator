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


int main(){
    void* ptr=malloc(1);
    printf("Address of malloc is %p\n", ptr);
	void* ptr1=malloc(5);
	printf("Address of malloc1 is %p\n", ptr1);
	void* ptr2 = malloc(1);
	printf("Address of malloc2 is %p\n", ptr2);
	free(ptr);
	printf("Successful free of %p\n", ptr);
	free(ptr1);
	printf("Successful free of %p\n", ptr1);
	free(ptr2);
	printf("Successful free of %p\n", ptr2);
    return 0;
}
