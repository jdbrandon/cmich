#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/*	main function for a3, takes 2 args and adds them together using the proper adders
	based on the input size. outputs the two inputs and their sum using RCA and LACA 
*/
int main(int argc, char **argv){
	int checkargs(int, char*, char*);
	void fadder(int,int,int,long*,int*);
	void rcadder4(int, int, int , long*, int*);
	void lacadder4(int, int, int, long*, int*);
	void rcadder32(int, int, int, long*, int*);
	void converttostring(long, unsigned char**);
	void lacadder32(int, int, int, long*, int*);
	void inttobinary(int, unsigned char**);
	int i,j,co;
	unsigned long int arg[2], result;
	unsigned char *overflow, *binary;
	arg[0]=0;
	arg[1]=0;
	result=0;
	i=1;
	while(i<argc){
		j=0;
		while(*(*(argv+i)+j)-'0'>=0){
			arg[i-1]*=10;
			arg[i-1]+=*(*(argv+i)+j)-'0';
			j++;
		}
		i++;
	}
	inttobinary(arg[0],&binary);
	fprintf(stderr,"n1:\t\t%lu\t(%s)\n",arg[0],binary);
	inttobinary(arg[1],&binary);
	fprintf(stderr,"n2:\t\t%lu\t(%s)\n",arg[1],binary);

	//program
	if(!checkargs(argc,*(argv+1),*(argv+2))) exit(0);
		
	if(arg[0]<=1&&arg[0]>=0&&arg[1]<=1&&arg[1]>=0){
		fadder(arg[0],arg[1],0,&result,&co);
		printf("n1+n2:\t\t%lu\t(%lu)\n", result,result);
	}
	else 	if(arg[0]<=15&&arg[0]>=0&&arg[1]>=0&&arg[1]<=15){
			rcadder4(arg[0],arg[1],0,&result,&co);
			inttobinary(result,&binary);
			printf("n1+n2(RCA):\t%lu\t(%s)\n", result,binary);
			lacadder4(arg[0],arg[1],0,&result,&co);
			inttobinary(result,&binary);
			printf("n1+n2(LACA):\t%lu\t(%s)\n", result,binary);

		}
	else	if(arg[0]<=4294967295u&&arg[0]>=0&&arg[1]<=4294967295u&&arg[1]>=0){
			rcadder32(arg[0],arg[1],0,&result,&co);
			inttobinary(result,&binary);
			if(co){
				overflow=malloc(10); 
				converttostring(result,&overflow);
				printf("n1+n2(RCA):\t%s\t(1%s)\n", overflow,binary);
			}
			else{
				printf("n1+n2(RCA):\t%lu\t(%s)\n", result,binary);
			}
			lacadder32(arg[0],arg[1],0,&result,&co);
			inttobinary(result,&binary);
			if(co){
				overflow=malloc(10); 
				converttostring(result,&overflow);
				printf("n1+n2(LACA):\t%s\t(1%s)\n", overflow,binary);
			}
			else{
				printf("n1+n2(LACA):\t%lu\t(%s)\n", result,binary);
			}

		}
	exit(0);

}
