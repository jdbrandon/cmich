/*	A5.c is an implementation of 1 bit error detection and correction
	using Hamming's code. The main function initializes variables and 
	functions and then iterates through each input in the file and 
	converts the integer to a binary representation, makes the binary
	string into it's hamming code and then displays the results.
 */

#include<stdio.h>
#include<stdlib.h>

int main(){
	int n;
	char*  message,*codedmessage;
	void xtractmessage(int, char**);
	void makemessage(char*,char**);
	void printresults(char*,char*);
	while(scanf("%d",&n)!=EOF){
		xtractmessage(n,&message);
		makemessage(message,&codedmessage);
		printresults(message, codedmessage);
	}
	exit(0);
}

/*	This function "xtractmessage" is designed to take an input integer
	and convert it to its binary representation. To do this the 
	number is divided by 2 and the remainder is recorded and then the 
	reverse order of the remainders corresponds to the numbers binary
	representation. This is returned as a string in *message.
 */

void xtractmessage(int n, char** message){
	char *binary;
	int i;
	void reversestr(char**);
	binary=malloc(17);
	i=0;
	if(n==0){binary[i]='0';i++;}
	while(n>0&&i<16){
		binary[i]=n%2+'0';
		n/=2;
		i++;
	}
	binary[i]=0;
	reversestr(&binary);
	*message=binary;
}
/*	Reversestr takes an input string and returns the 
	reverse of it. To do this a counter is used to iterate
	through the length of the string and then it iterates
	through the string backwards copying it to a destination
	string which is then returned as the result.
 */
void reversestr(char **str){
	int i,j;
	i=0;
	char *result;
	result=malloc(sizeof(*str));
	while(*(*(str)+i)) i++;
	i--;
	j=0;
	while(i>=0){
		result[j]=*(*(str)+i);
		i--;
		j++;
	}
	result[j]=0;
	*str = result;
}
/*	Makemessage takes an input string of binary characters and converts it
	to its corresponding hamming code. To do this the number of redundant bits
	is first determined by incrementing the number of redundant bits until the 
	defining equation of m+r+1<=2^r is satisfied where m is the size of the string
	and r is the number of redudndent bits. Then the string is copied to
	a code string with the redundant bits inserted in their appropriate locations
	then a count of numbers pretaining to each redundent bit is kept and then is 
	used to figure out if a redundant bit is zero or one by taking the counts 
	remainder. If the remainder is 0 then the redundent bit is also 0 and likewise
	is 1 when the remainder is 1. The resulting coded string is then returned.
 */
void makemessage(char* msg,char** m){
	int i,j,size,redundantbitcount, count1,count2,count4,count8,count16;
	char *code;
	size = count1 = count2 = count4 = count8 = count16 = 0;
	while(*(msg+size))size++;
	redundantbitcount=0;
	while(size+redundantbitcount+1>(1<<redundantbitcount))redundantbitcount++;
	code=malloc(size+redundantbitcount);
	j=0;
	i=2;
	while(j<size){
		if(i==3||i==7||i==15) i++;
		code[i]=msg[j];
		if(i%2==0 && i!=0)
			if(code[i]=='1') count1++;
		if(i+1==3||i+1==6||i+1==7||i+1==10|| \
			i+1==11||i+1==14||i+1==15||i+1==18||i+1==19)
				if(code[i]=='1') count2++;
		if(i+1==5||i+1==6||i+1==7||i+1==12|| \
			i+1==13||i+1==14||i+1==15||i+1==20||i+1==21) 
				if(code[i]=='1') count4++;
		if(i+1==9||i+1==10||i+1==11||i+1==12|| \
			i+1==13||i+1==14||i+1==15) 
				if(code[i]=='1') count8++;
		if(i+1==17||i+1==18||i+1==19||i+1==20||i+1==21)
			if(code[i]=='1') count16++;
		i++;
		j++;
	}
	code[i]=0;
	
	code[0]=count1%2+'0';
	code[1]=count2%2+'0';
	if(redundantbitcount>=3) code[3]=count4%2+'0';
	if(redundantbitcount>=4) code[7]=count8%2+'0';
	if(redundantbitcount>=5) code[15]=count16%2+'0';
	*m=code;		
}
/*	Printresults takes two input strings corresponding to the input message
	and the resulting hamming code and prints out the strings and 
	the redundant bits and their values.
 */
void printresults(char* msg, char* code){
	int sizemsg,sizecode,power;
	sizemsg=sizecode=0;
	while(*(msg+sizemsg))sizemsg++;
	while(*(code+sizecode))sizecode++;
	printf("Uncoded message:\t%s\n",msg);
	printf("Redundent bits:\t\t1:%c 2:%c",code[0],code[1]);
	power=2;
	while(1<<power<sizecode){ 
		printf(" %d:%c",1<<power,code[(1<<power)-1]);
		power++;
	}
	printf("\nCoded Message:\t\t%s\n\n",code);	
}
