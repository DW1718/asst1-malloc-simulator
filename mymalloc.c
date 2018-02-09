/* CS214 SYSTEMS PROGRAMMING ASST1 BY FREDERICK WILLIAM LAU AND JAROOR MODI*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include "mymalloc.h"


static char mainMem[5000];

node_t *head=NULL;

void createNode(node_t* temp, int size, int location){
	printf("In createNode, size is %d\n", size);
	//nodeEntry temp = calloc(1, sizeof(node_t));
	temp->addr=&mainMem[location];
	temp->size=size;
	temp->location=location;
	temp->next=NULL;
}

void* mymalloc(int size){
	printf("In mymalloc, size is %d\n", size);
	int location=0;
	int memSize=size;
	node_t *curr = head;
	//empty list means nothing malloced yet
	if(curr==NULL){
		node_t *insert = calloc(1, sizeof(node_t));
		createNode(insert, memSize, location);
		curr=insert;
		printf("In mymalloc, head is empty, created node with size %d at location %d\n", size, location);
		return insert->addr;
	}
	//shit has been malloced, need to find first adequate space in memory
	else{
		//puts us at the first node representing
		//malloced memory
		node_t *curr = head;
		int didInsert=0;
		int memUsed=0;
		while(curr->next!=NULL){
			curr=curr->next;
			//there is available memory between curr node
			// and next node and
			//is enough to malloc what we need
			if(curr->next!=NULL&&(curr->next->location-(curr->size+curr->location))>=memSize){
				location=curr->size+curr->location;
				node_t *insert = calloc(1, sizeof(node_t));
				createNode(insert, memSize, location);
				insert->next=curr->next->next;
				curr->next=insert;
				didInsert=1;
				return insert->addr;
			}
			//there is not enough free space between these two
			//"regions" of allocated memory to malloc what we
			//need, keep iterating until we find a sufficient
			//space or get to the end of our allocated memory
			//region, keep track of memory used to be sure we
			//don't exceed our main memory capacity
			else{
				memUsed+=curr->size;
				continue;
			}
		}
		//we got to the end of our allocated memory and did NOT
		//insert anything, and we have enough space at the end
		//of our allocated memory region for our malloc, insert
		//at end
		if(!didInsert&&(5000-curr->location+curr->size)){
			location=curr->size+curr->location;
			node_t *insert = calloc(1, sizeof(node_t));
			createNode(insert, memSize, location);
			curr->next = insert;
			didInsert=1;
			return insert->addr;
		}
		//we either malloced successfully or there is no adequate
		//region of memory that we can malloc either in the middle
		//of the array or at the end of the array
		else{
			printf("Error.  Unable to allocate memory of size %d\n", memSize);
			return NULL;
		}
	}
}

void myfree(void* ptr){
	node_t *curr=head->next;
	node_t *prev=head;
	node_t *post=curr->next;
	int didDelete=0;
	while(curr!=NULL){
		//found the pointer to "free"
		if(curr==ptr){
			prev->next=post;
			didDelete=1;
			break;
		}
		//did not find pointer to "free"
		//keep iterating
		else{
			curr=curr->next;
			prev=prev->next;
			post=post->next;
		}
	}
	//pointer does not exist
	if(!didDelete){
		printf("Error.  Cannot free a pointer that does not exist herpaderp\n");
		return;
	}
	return;
}



