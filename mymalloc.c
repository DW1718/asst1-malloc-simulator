/* CS214 SYSTEMS PROGRAMMING ASST1 BY FREDERICK WILLIAM LAU AND JAROOR MODI*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include "mymalloc.h"


static char mainMem[5000];


node_t *head=NULL;
void *prev_freed=NULL;

void createNode(node_t* temp, int size, int location){
	//printf("In createNode, size is %d\n", size);
	//nodeEntry temp = calloc(1, sizeof(node_t));
	temp->addr=&mainMem[location];
	temp->size=size;
	temp->location=location;
	temp->next=NULL;
}

void* mymalloc(int size, const char * file_name, int line_number){
	//printf("Mallocing size of %d\n", size);
	int location=0;
	int memSize=size;
	node_t *curr = head;
	//empty list means nothing malloced yet
	if(curr==NULL){
		head = calloc(1, sizeof(node_t));
		head->next = NULL;
		curr=head;
		node_t *insert = calloc(1, sizeof(node_t));
		createNode(insert, memSize, location);
		curr->next=insert;
		//~printf("Head is empty, created node with size %d at location %p\n", size, curr->next->addr);
		return insert->addr;
	}
	else if(curr->next==NULL){
		node_t *insert = calloc(1, sizeof(node_t));
		createNode(insert, memSize, location);
		curr->next=insert;
		//~printf("Head is NOT empty but .next is, created node with size %d at location %p\n", size, curr->next->addr);
		return insert->addr;
	}
	//memory has been malloced, need to find first adequate space in memory
	else{
		//puts us at the first node representing
		//malloced memory
		//~printf("List is NOT empty, finding space to malloc...\n");
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
				//~printf("Malloced middle region with size %d at address %p\n", insert->size, insert->addr);
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
			//~printf("Malloced at END region of size %d at address %p\n", curr->next->size, curr->next->addr);
			return insert->addr;
		}
		//we either malloced successfully or there is no adequate
		//region of memory that we can malloc either in the middle
		//of the array or at the end of the array
		else{
			printf("ERROR: In file %s line %d, unable to allocate memory block of size %d due to memory saturation.\n", file_name, line_number, memSize);
			return NULL;
		}
	}
}

void myfree(void* ptr, const char * file_name, int line_number){
	//printf("Attempting to free pointer %p...\n", ptr);
	if(ptr==NULL){
		printf("ERROR: In file %s line %d attempting to free NULL\n", file_name, line_number);
		return;

	}
	if (ptr==prev_freed){
		printf("ERROR: In file %s line %d attempting to free pointer consecutive times without malloc()ing.\n", file_name, line_number);
		return;
	}
	node_t *curr=head->next;
	node_t *prev=head;
	node_t *post=curr->next;
	int didDelete=0;
	while(curr!=NULL){
		//found the pointer to "free"
		if(curr->addr==ptr){

			prev->next=post;
			didDelete=1;
			//printf("Freed address %p!\n", curr->addr);
			ptr = NULL;//what is this for?
			break;
		}
		//did not find pointer to "free"
		//keep iterating
		else{
			if(curr->next==NULL){
				break;
			}
			curr=curr->next;//segfault here
			prev=prev->next;
			post=post->next;
		}
	}
	//pointer was not malloc()ed since last free()ing.
	if(didDelete == 0){
		printf("ERROR: In file %s line %d attempting to free pointer which was not malloc()ed.\n", file_name, line_number);
		return;
	}
	prev_freed = ptr;
	return;
}
