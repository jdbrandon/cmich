/* 	Main is designed to to test the efficiency of regular functions 
	against leaf functions. To do this in a loop that iterates 
	100000 times, identical strings are initialized and then one set 
	is operated on by leaf functions and the time is added to a total 
	leaf function time. The other identical strings are then operated 
	on by regular functions and the time it takes to complete the 
	regular function calls is recorded and then added to a total 
	normal function time. Then once the loop completes, the total time
	for the leaf functions and the total time for the normal functions
	is printed out to the user along with the difference between them
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>
int main()
{
	struct timeval t1,t2;
	int count, data[22] = { 1, 2, 3, -3, -99, 999, 42, 14, 56, 
				76, 99, 12, -2345, 3456789, 199, 123,
				234, -567, -999, 21, 32, -12345};
	int z,i;
	i=0;
	long long timeleaf, timenorm, difference;
	void lstringcpy(char *dst, char *src);
	void stringcpy(char *dst, char *src);
	void lstringcat(char *dst, char *src);
	void stringcat(char *dst, char *src);
	void lreversestr(char *st);
	void reversestr(char *st);
	void lstringucase(char *st);
	void stringucase(char *st);
	void lstringlcase(char *st);
	void stringlcase(char *st);
	int lstringcmp(char *str1, char *str2);
	int stringcmp(char *str1, char *str2);
	int lcntofevens(int *list, int n);
	int cntofevens(int *list, int n);
	int lfindlargest(int *list, int n);
	int findlargest(int *list, int n);
	int lcntlessthanx(int *list, int n, int x);
	int cntlessthanx(int *list, int n, int x);
	int lcntofmultiplesof8(int *list, int n);
	int cntofmultiplesof8(int *list, int n);
	
	timeleaf = 0; timenorm = 0;
	
	while(i<100000){
	char astr[64] = "A long long string is here!!";
	char astr2[64]= "A long long string is here!!";
	char *str = "True";
	char *str2= "True";
	char s[4]="Tru";
	char s2[4]="Tru";
	char *t="e";
	char *st2="e";
	char backwards[15]="eurT";
	char backwards2[15]="eurT";
	/* start timer for leaf */
	gettimeofday(&t1,NULL);
	lstringcpy(astr, str);
	lstringcat(s,t);
	lreversestr(backwards);
	lstringucase(s);
	lstringlcase(s);
	z = lstringcmp(s,str);
	count = lcntofevens(data, 22);
	count = lfindlargest(data, 22);
	count = lcntlessthanx(data,22,0);
	count = lcntofmultiplesof8(data,22);
	gettimeofday(&t2,NULL);
	/* end timer for leaf */
	timeleaf+=t2.tv_usec-t1.tv_usec;	
	/* start timer for normal */
	gettimeofday(&t1,NULL);
	stringcpy(astr2, str2);
	stringcat(s2,st2);
	reversestr(backwards2);
	stringucase(s2);
	stringlcase(s2);
	z = stringcmp(s2,str2);
	count = cntofevens(data, 22);
	count = findlargest(data, 22);
	count = cntlessthanx(data,22,0);
	count = cntofmultiplesof8(data,22);
	gettimeofday(&t2,NULL);
	/* end timer for normal */
	timenorm+=t2.tv_usec-t1.tv_usec;
	difference=timenorm-timeleaf;
	i++;
	}
	printf("leaf time: %lld\nnormal time: %lld\ndifference: %lld\n",timeleaf,timenorm,difference);
	exit(0);
}
