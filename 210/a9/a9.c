#define SIZE 32
#include <stdio.h>
#include <stdlib.h>
struct set{
	char *data;
	int count;
};

typedef struct set set;

/*	makeaset is designed to make a set, to do this it allocates 
	storage and makes the set s1 empty, and handles 
	the count of elements. The function uses malloc() to allocate 
	memory for the set and its data portion with size SIZE.
 */

void makeaset(set **s1){
	int i; set *ptr;
	
	ptr = NULL;
	ptr = malloc(sizeof(set));
	if(ptr){
		ptr->data = malloc(SIZE);
		if(ptr->data){
			for(i=0; i<SIZE; i++) ptr->data[i] = 0;
			ptr->count = 0;
		}
	}
	*s1 = ptr;
}

/*	The function clearaset is designed to clear the data portion of 
	the input set which makes the passed set empty, bits and count 
	are cleared using iterations through the SIZE of the data portion
	and making them 0.
 */

void clearaset(set *s2){
	int i;

	s2->count = 0;
	for(i=0; i<SIZE; i++)
		s2->data[i] = 0;
}

/*	The function addtoset is for adding the given element to the set 
	passed as an argument and updates the counter. To do thismthe
	function first checks if the element is in the domain of the set
	struct. If it is, then the value at n/8 (int division) is assigned
	the result of its current value in an OR operation with 1 bit, shifted
	left by n%8 which effectively sets the nth bit of the sets data segment
	to 1, signifying n is a member of the set. The the set's count member
	is incremented also because the set has grown by one element.
 */
void addtoset(int elm, set *s1){
	if(elm>=0 && elm<=255){
		s1->data[elm/8] = (s1->data[elm/8]) | (1<<(elm%8));
		s1->count++;
	}
}

/*	The function isinset is designed to determine if a particular
	element is a member of a set. To do this the function checks 
	to see if the argument is in the set by first making sure
	the sets size is greater than 0. If it is, it then checks if 
	the element to be searched for is within the domain of the set.
	If it is the function then checks if the result of the and 
	operation of data[n/8] and (1<<n%8) is nonzero, and if it is
	the function returns 1 for true, and in all other cases the 
	function returns 0 for false, the element is not a member of 
	the set.
 */

int isinset(int elm, set *s1){
	if(s1->count==0) return 0;
	if(elm<0 || elm>255) return 0;
	if(s1->data[elm/8]& 1<<(elm%8)) return 1;
	else return 0;
}

/*	The function setunion is designed to take s1 and s2, perform the
	union operation on them and store the resulting set in s3. To do
	this, a counter variable is set to 0 and is used to iterate through
	the data portion of s1 and s2. In the afformentiond loop, the result
	of the or operation on the data segments of s1 and s2 is stored in the
	corresponding data segment of the pointer. Once the loop is finished the 
	address of the pointer variable is assigned to s3. Also just in case
	s3 is null, makeaset() is called on it in the beginning of the module.
 */

void setunion(set *s1, set *s2, set **s3){
	int i,j; set *ptr;
	makeaset(s3);
	ptr = *s3;
	ptr->count=0;
	for(i=0; i<SIZE; i++){
		ptr->data[i] = (s1->data[i]) | (s2->data[i]);
		for(j=0;j<8;j++)
			if(ptr->data[i] & 1<<j) ptr->count++;
	}
	*s3 = ptr;
}

/*	The function setintersect takes s1 and s2, performs the set intersect
	operation on them and stores the results of that operation in s3.
	To do this, a counter variable and a pointer to a set are declared and
	used to iterate through the length of the data segments of s1 and s2. 
	In this loop, the result of the 2 repective data segments from s1 and 
	s2 being put into an AND operation is stored in the value of the pointers 
	respective data segment value. Lastly, the address of the pointer is 
	assigned to s3. Also incase s3 is null, makeaset() is called on it at
	the beginning of the module.
 */

void setintersect(set *s1, set *s2, set **s3){
	int i,j; set *ptr;
	makeaset(s3);
	ptr = *s3;
	ptr->count = 0;
	if(s3==NULL) makeaset(s3);
	for(i=0; i<SIZE; i++){
		ptr->data[i] = (s1->data[i]) & (s2->data[i]);
		for(j=0; j<8; j++)
			if(ptr->data[i] & 1<<j) ptr->count++;
	}
	*s3 = ptr;
}

/*	The function setdiff takes s1 and s2, performs the set difference
	operation on them, and stores the results in s3 to be returned.
	To do this, an interator variable is initialized to 0 and used to
	pass through each value in the data segment of the two input sets
	and the data segment of a pointer variable. the data of the pointer
	variable is assigned the result of s1's data being exclusive or'ed
	(XOR) with s2's data then ANDed with the original s1 data segment.
	This sets all bits that are turned on in both sets to 0, then by 
	ANDing that with the original s1 data, only the elements exclusively
	found in s1 have their respective bits turned on in the result. 
	Which removes elemetns from s1 that are also in s2. Lastly, s3 is 
	assigned the address of the pointer variable. Also, just in case
	s3 is null, makeaset() is called on it in the beginning of the
	module.
 */

void setdiff(set *s1, set *s2, set **s3){
	int i,j; set *ptr;
	makeaset(s3);
	ptr = *s3;
	ptr->count = 0;
	if(s3==NULL) makeaset(s3);
	for(i=0; i<SIZE; i++){
		ptr->data[i] = ((s1->data[i])^ (s2->data[i]))& s1->data[i];
		for(j=0; j<8; j++)
			if(ptr->data[i] & 1<<j) ptr->count++;
	}
	*s3 = ptr;
}

/*	The function dosetops performs the set operations and prints results as 
	needed, results must be cleared after each operation. To do this, an
	address of an address of a set is declared then passed to makeaset().
	this variable serves as the result set for the operations to be performed
	on the passed sets A and B. First printaset() is called on A and B 
	respectively to show what the values of the original sets are, then
	setunion() is called and printaset() is called on the result. After this
	clearaset() is called on the result to make it empty again. This process 
	repeats with setintersect() and setdifferenc(). setdifference() is called
	twice, once for the operation of A-B and once for the operation B-A.
	After each function call to an operation, the result has printaset() 
	called on it before clearaset() makes the result variable empty agian.
	at the end, of dosetops() freeaset is called on the result to restore
	the memory allocated for the result back to the heap. 
 */

void dosetops(set *seta, set *setb){
	void printaset(char *, set *);
	void freeaset(set **);
	set **res, *ptr, s;
	ptr = &s;
	res = &ptr;
	makeaset(res);
	printaset("Set A", seta);
	printaset("Set B", setb);
	setunion(seta, setb, res);
	printaset("A union B", *res); 
	clearaset(*res);
	setintersect(seta, setb, res);
	printaset("A intersect B", *res);
	clearaset(*res);
	setdiff(seta, setb, res);
	printaset("A difference B", *res);
	clearaset(*res);
	setdiff(setb, seta, res);
	printaset("B difference A", *res);
	freeaset(res);
}

/*	The function printaset writes the label followed by the elements of 
	s1 to stderr. To do this The lable is first printed to stderr and 
	then a check is done to see if the count of the passed set is 0 or
	not. If it is 0, the 'empty' is printed to stderr and if not 2 counter
	variables are used to iterate through the size of the data segment and 
	then each bit of each element of the datasegment. For each bit that is
	turned on, the number associated with that bit is printed out by 
	multiplying the index of the data segment by 8 and then adding in the 
	position of the bit in that data segment. Once the interations are 
	complete every number in the set has been printed to stderr.
 */

void printaset(char *label, set *s1){
	int i,j,k;
	k = s1->count;
	fprintf(stderr,"%s: ", label);
	if(k==0){ fprintf(stderr,"empty");}
	else{
		for(i=0; i<SIZE; i++){
			if(s1->data[i]){
				for(j=0; j<8; j++){
					if(s1->data[i] & (1<<j))
						fprintf(stderr,"%d ",(i*8)+j);
				}
			}
		}
	}
	fprintf(stderr,"\n");
}

/*	The function buildaset populates the set using values read from
	stdin, also updates the count member by using the addtoset() 
	module. To do this a user promt asks for the number of elements
	the set to built will have. If the number is less than or equal to 
	0, clearaset is called on the set and it is made into the empty set. 
	If the number read is positive, then the user is promted to enter in
	a number that will be an element of the set. After each element is 
	added to the set using addtoset(), the number of elements left to 
	read is decremented and this process of reading an element and adding 
	it to the set with addtoset() repeats until the number of elements 
	left to read is zero.
 */

void buildaset(set *s1){
	int num, i;
	fprintf(stderr, "Enter the count of elements to be entered\n");
	scanf("%d",&num);
	if(num<=0) clearaset(s1);
	else{
		fprintf(stderr,"Enter values to populate the set from 0-255\n");
		while(num>0){
			scanf("%d", &i);
			addtoset(i, s1);
			num--;
		}
	}
}

/*	The function freeaset returns storedage allocated by malloc()
	back to the system.
 */

void freeaset(set **s1){
	set *s2;

	s2 = *s1;
	if(s2 != NULL){
		free((void*)s2);
		*s1 = NULL;
	}
}
