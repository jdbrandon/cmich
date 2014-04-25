/*	eval1 computes the factorial function
	eval2 computes sum of squares from one to twice the input 
	parameter minus one.
	eval3 computes a base taken to one less than a given exponent
	eval4 determines if the input parameter is a perfect number
	eval5 finds the greatest common divisor of two input 
	parameters
 */

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int a, b, d, x, y, z, eval1(int), eval2(int), 
eval3(int,int), eval4(int), eval5(int,int);
	a = 3; b = 5; d = 7;
	x = eval1(b);
	printf("if eval1 works properly 120 =  5! = %d\n",x);
	y = eval2(3);
	printf("if eval2 works properly 5+9+16+25 = %d\n",y);
	z = eval3(d,a);
	printf("if eval3 works properly 7^(3-1) = 49 = %d\n",z);
	if(eval4(6)==1) printf("6 is a perfect number\n");
	if(eval4(7)!=1) printf("7 is not a perfect number\n");
	a = eval5(x,y);
	printf("if eval5 works then %d is the gcd of %d",a,x);
	printf(" and %d.\n",y);
	exit(0);
} 
