/*Header file for mymalloc.c and memgrind.c, defines functions that will be used in both files*/
#ifndef MYMALLOC_H_
#define MYMALLOC_H_

#define malloc(x) mymalloc(x,__FILE__,__LINE__)
#define free(x) myfree(x,__FILE__,__LINE__)

void* mymalloc (int size, const char * file_name, int line_number);
void myfree (void* ptr, const char * file_name, int line_number);

typedef struct pointerNode{
	char* addr;
	int size;
	int location;
	struct pointerNode* next;
}node_t;
//typedef node_t* nodeEntry;

#endif
