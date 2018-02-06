#ifndef MYMALLOC_H_
#define MYMALLOC_H_

#define malloc(x) mymalloc(x,__FILE__,__LINE__)
#define free(x) myfree((void*)(x),__FILE__,__LINE__)

void* mymalloc(int size, char* errLoc, int errLine);
void myfree(void* ptr, char* errLoc, int errLine);

typedef struct pointerNode {
	int confirm;
	void* allocMem;
	int size
	int isFree;
	struct pointerNode* prev;
	struct pointerNode* next;
} node_t;
typedef pointerNode* theNode;

#endif