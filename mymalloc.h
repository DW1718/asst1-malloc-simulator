/*Header file for mymalloc.c and memgrind.c, defines functions that will be used in both files*/
#ifndef MYMALLOC_H_
#define MYMALLOC_H_

#define malloc(x) mymalloc(x)
#define free(x) myfree(x)

void* mymalloc (int size);
void myfree (void* ptr);

typedef struct pointerNode{
	char* addr;
	int size;
	int location;
	struct pointerNode* next;
}node_t;
//typedef node_t* nodeEntry;

#endif
