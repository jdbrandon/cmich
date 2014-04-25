/*
	Explore n-way associative cache memory. Macros and structs
	are declared and defined. Line is a struct that contains a
	tag. Each cache entry is made up of an array of lines, in this
	case L1 cache has a 2 line array and L2 cache has a 4 line array.
	Each cache struct also has a killpointer which holds an integer
	value that relates to the index of the line that needs to be 
	replaced next. The structs l1 and l2 are initialized to the
	cache size divided by the number of lines in a set for that 
	cache. This is done using a bitshift rather than division.
 */

#include <stdlib.h>
#include <stdio.h>

#define L1_CACHE_SIZE 32768
#define L2_CACHE_SIZE 65536

struct line{
	int tag;
};

typedef struct line line;

struct L1{
	line set[2];		
	int killptr;
};

typedef struct L1 L1;

struct L2{
	line set[4];
	int killptr;
};
typedef struct L2 L2;

L1 l1[L1_CACHE_SIZE>>1];
L2 l2[L2_CACHE_SIZE>>2];

long l1misses, l2misses, references;

/*	In the main function variables and functions are declared. Reference is
	used to reference an address from the input stream, printresults is
	used to display the results after each input address has been referenced
	the integer i is used for iterative purposes, the unsigned address is used 
	to hold the value of the address most recently scanned from input. Then
	the number of references, and misses for each cache are initialized to 0.
	Then i is used to iterate through each cache and initialize each set in
	l1 and l2 to 0 and also the killptr for each set, this effectively makes 
	all cache entries invalid because the valid bit is not set. Next input
	is processed from the scanf function and stored in the address variable.
	Once the value is stored in address, the reference function is called 
	with address as its parameter. After all inputs are processed printresults
	is called to display the data and then the functions exits normally.
 */

int main(){
	void reference(unsigned);
	void printresults();
	int i;
	unsigned address;
	l1misses=l2misses=references=0;
	for(i=0;i<(L1_CACHE_SIZE>>1);i++){
		l1[i].set[0].tag=l1[i].set[1].tag=l2[i].set[0].tag= 
		l2[i].set[1].tag=l2[i].set[2].tag=l2[i].set[3].tag=
		l1[i].killptr=l2[i].killptr=0;
	}
	while(scanf("%x",&address)!=EOF){
		reference(address);
	}
	printresults();
	exit(0);
}

/*	In the reference function, a given 32 bit address is processed and determines if
	the address is a hit or miss in both l1 and l2 cache. To do this functions like
	isL1hit and isL2hit are used. First variables are declared such as setindex which
	holds the index of the set where the address will be found if it is in a cache, tag
	which holds the unique identifier for an address, and i which is used iteratively.
	set is also declared to be used for finding a kill target in l2 when a replacement is
	neccessary in l1. Then setindex and tag are initialized to their respective values 
	using the adress passed to the function. If isL1hit returns true then the killptr is
	advanced if it currently points to the line that was referenced. If l1 does not have a 
	hit l1misses is incremented and l2 is checked for a hit or a miss using isL2hit. If it
	returns true, l2's kill ptr is advanced accordingly and the replacement is made in l1 
	at the killptr line. Also worth noting, whenever a tag is added to a line, its bitshifted
	to the left by one then has one added to it, this least significant bit is used as a valid
	bit. Then the l1 killptr is incremented. If l2 has a miss also, l2misses is incremented
	and then the lines of l2 are iterated through to check for any entries that are still 
	invalid, if any are the first one encountered has the killpointer set to it and iteration
	stops because 'set' is set to 1. If there are no invalid entries then l2 is iterated
	through once more to find the line with a tag equal to the tag of the l1 line at killptr.
	This line is then the replacement target in l2, the killptr is set to its index that is.
	Once replacement targets are determined for both sets, replacements are made at killptr
	in each set and then the killptr is incremented. Every time the reference function is 
	called the references variable is incremented also.
 */
void reference(unsigned adr){
	int isL1hit(int, int);
	int isL2hit(int, int);
	int setindex, tag,i;
	char set;	
	setindex=(adr>>6)&((1<<14)-1);
	tag=adr>>20;
	if(isL1hit(tag,setindex)){
		if(l1[setindex].killptr==isL1hit(tag, setindex)-1)
			l1[setindex].killptr++;
			l1[setindex].killptr%=2;	
	}
	else{
		l1misses++;
		if(isL2hit(tag, setindex)){
			if(l2[setindex].killptr==isL2hit(tag,setindex)-1){
				l2[setindex].killptr++;
				l2[setindex].killptr%=4;
			}
			l1[setindex].set[l1[setindex].killptr].tag=(tag<<1)+1;
			l1[setindex].killptr++;
			l1[setindex].killptr%=2;
		}
		else{
			l2misses++;
			i=0;
			set=0;
			while(i<4 && !set){
				if(!(l2[setindex].set[i].tag & 1)){
						l2[setindex].killptr=i;
						set=1;
					}
				i++;
			}
			if(!set){
				for(i=0;i<4;i++)
					if(l1[setindex].set[l1[setindex].killptr].tag==
						l2[setindex].set[i].tag)
							l2[setindex].killptr=i;
			}
			l1[setindex].set[l1[setindex].killptr].tag=(tag<<1)+1;
			l1[setindex].killptr++;
			l1[setindex].killptr%=2;
			l2[setindex].set[l2[setindex].killptr].tag=(tag<<1)+1;
			l2[setindex].killptr++;
			l2[setindex].killptr%=4;
		}
	}
	references++;
}

/*	The function isL1hit takes a given tag and index and determines if it
	is in the L1 cache and if it is, returns the index of the line where 
	it is stored. To do this l1 is iterated through at the set index 
	searching for a matching tag (with a valid bit). The index offset 
	by one is returned to that when the hit is found at index zero
	the function still returns true and then the outpust just has to 
	have the offset accounted for. If no match is found, a miss has 
	occured and 0 is returned.
 */
int isL1hit(int tag, int index){
	int i;
	for(i=0;i<2;i++)if(l1[index].set[i].tag==(tag<<1)+1)return i+1;
	return 0;
}

/*
	The function isL2hit performs very similarly to isL1hit except 
	that instead of dealing with the L1 cache, it deals with the 
	L2 cache. Given a tag and a setindex, the given set is iterated
	through searching for a matching tag, then if a match is found
	a hit has occured and the index offset by 1 is returned. Again 
	this offset is to prevent a hit at index 0 to be treated as a miss.
	The output just has to be handled as offset by one and the result
	performs as expected. If no match is found, a miss has occured and
	0 is returned.
 */
int isL2hit(int tag, int index){
	int i;
	for(i=0;i<4;i++)if(l2[index].set[i].tag==(tag<<1)+1) return i+1;
	return 0;
}

/*	The function printresults displays the data collected in a readable format.
	It displays the number of L1 misses, L2 misses, and the number of total
	references from the give input stream.
 */
void printresults(){
	printf("L1 misses = %ld\nL2 misses = %ld ",l1misses,l2misses);
	printf("(L1 Misses = %ld)\n",l1misses); 
	printf("References = %ld\n",references);
}
