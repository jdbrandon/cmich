/*	Main tesets the modules by initializing sets then building them, and 
	performing the set operations on them using the dosetops() method
	a set in this context is a struct that holds two fields. First
	a C-String that is used to hold data, each bit in the data field
	is used to represent the nth element of the set and if the bit is
	turned on (in this case 1) that element is a member of the set.
	The second element is the count which is an integer used to keep
	track of how many elements are in the set.
 */
#include <stdio.h>
#include <stdlib.h>
#define SIZE 32

struct set{
	char *data;
	int count;
};

typedef struct set set;

int main(void){
	
	set *a, *b;
	a = malloc(4);
	b = malloc(4);
	void makeaset(set **);
	void clearaset(set *);
	void addtoset(int, set *);
	int isinset(int, set *);
	void setunion(set *, set *, set **);
	void setintersect(set *, set *, set **);
	void setdiff(set *, set *, set **);
	void dosetops(set *, set *);
	void printaset(char *, set *);
	void buildaset(set *);
	void freeaset(set *);

	makeaset(&a);
	makeaset(&b);
	buildaset(a);
	buildaset(b);
	dosetops(a,b);
	clearaset(a);
	dosetops(b,a);
	if(!isinset(2,b)) fprintf(stderr,"\nfalse case is in set works\n");
	if(isinset(1,b)) fprintf(stderr,"\ntrue case is in set works\n");
	freeaset(a);
        freeaset(b);
	exit(0);
}
