/*	This program is designed to simulate a cache of 8192 lines with
	32 bit address and 32 byte data block
 */

#include <stdlib.h>
#include <stdio.h>
#define CACHE_SIZE 8192
#define BLOCK_SIZE 5

struct line{
	int tag;
	char valid;
	/* int data; */
};

typedef struct line line;
line cache[CACHE_SIZE];
long references, misses;

int main(){
	void reference(unsigned);
	unsigned addr;
	int i;
	misses = references = 0;
	for(i=0;i<CACHE_SIZE;i++) cache[i].tag = cache[i].valid=0;
	while(scanf("%x",&addr)!=EOF){
		reference(addr);
	}	
	printf("This address stream had %ld references and %ld misses.\n",references,misses);

	exit(0);	
}

void reference(unsigned a){
	int index,tag;
	/* extract least significant 19 bits */
	index=(a<<(32-13))>>(32-13);
	tag=a>>13;
	if (cache[index].valid!=1 || cache[index].tag!=tag){
		cache[index].tag=tag;
		cache[index].valid=1; 
		misses++;
	}
	references++;
}
