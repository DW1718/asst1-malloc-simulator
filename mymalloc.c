#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "mymalloc.h"

static char mainMem[5000];

/*typedef struct pointerNode {
	int confirm;
	void* allocMem;
	int size
	int isFree;
	struct pointerNode* prev;
	struct pointerNode* next;
} node_t;
typedef pointerNode* theNode;*/

void insertMem(theNode head, int size, theNode prev, theNode next){
	head->confirm=1;
	head->allocMem=((void*)head)+sizeof(node_t);
	head->size=size;
	head->isFree=0;
	head->prev=prev;
	head->next=next;
}

void* mymalloc(int size, char* errLoc, int errLine){
	//error checking for uninitialized memory or exceeding memory space
	if(mainMem==NULL){
		printf("Error.  Main memory uninitialized...\n");
		return NULL;
	}
	if(size<=0||size>5000){
		printf("Error.  Unable to allocate memory of size %d\n", size);
		return NULL;
	}
	theNode tempHead = (theNode) mainMem;
	theNode tempPrev=NULL;
	theNode tempNext=NULL;

	int temp=5000;
	while(1){
		//checks if pointer is initialized
		if(head->confirm){
			if(temp>=(sizeof(node_t)+size)){
				insertMem(tempHead, size, tempPrev, tempNext);
				if(tempPrev!=NULL){
					tempPrev->next=tempHead;
				}
				return tempHead->allocMem;
			}
			printf("Error.  No memory available...\n");
			return NULL;
		}
		//checks if current memory is free and if it has enough space
		tempPrev=tempHead->prev;
		tempNext=tempHead->next;
		if(tempHead->isFree==1 && tempHead->size>=size){
			//checks previously allocated memory to see if it is larger then
			//what the user asked for and creates an entry to manage that space
			if(tempHead->size>size+sizeof(node_t)){
				void *entry=(void*)tempHead+sizeof(node_t)+size;
				theNode tempNode=(theNode) voidEntry;
				insertMem(tempNode, tempHead->size-size-sizeof(node_t), tempHead, tempHead->next);
				insertMem(tempHead, size, tempPrev, tempEntry);
				free((void*)tempEntry+sizeof(node_t));
				return tempHead->allocMem;
			}
			else{
				tempHead->isFree=0;
				return tempHead->allocMem;
			}
		}
		if(tempHead->next != NULL){
			tempHead=tempHead->next;
		}
		else if((void*)tempHead+sizeof(node_t)+tempHead->size<=(void*)mainMem+5000-sizeof(node_t)){
			tempPrev=tempHead;
			tempNext=NULL;
			void* rmHead=(void*)tempHead+sizeof(node_t)+tempHead->size;
			tempHead=(theNode) rmHead;
		}
		else{
			printf("Error.  No memory available...\n");
			return NULL;
		}
		temp=(void*)mainMem+5000-(void*)tempHead;
	}
}

void myfree(void* ptr, char* errLoc, int errLine){
	theNode trash = (theNode)(ptr-sizeof(node_t));
	//valid pointer?
	if(!((void*)mainMem<=(void*)trash&&(void*)trash<(void*)(mainMem+5000-sizeof(node_t)))){
		printf("Error.  Invalid pointer...Out of Range...\n");
		return;
	}
	//valid initialized pointer?
	if(trash->confirm==0){
		printf("Error.  Invalid pointer...\n");
		return;
	}
	//already free?
	if(trash->isFree){
		printf("Error.  Pointer has already been freed...\n");
		return;
	}
	//free
	trash->isFree=1;
	//adjusts nodes to check previous and next pointers
	if(trash->next !=NULL&&trash->next->isFree){
		trash->size = trash->size+trash->next->size+sizeof(node_t);
		trash->next=trasn->next->next;
	}
	if(trash->prev!=NULL&&trash->prev->isFree){
		trash->prev->size = trash->prev->size+trash->size+sizeof(node_t);
		trash->prev->next=trash->next;
	}
}
