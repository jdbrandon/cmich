/* This starts a comment..
	First program in 210 by Jeff Brandon
	Section: 22169660
	Assignment: 1,		Pints: 10
	Done on 1/14/12
	Look at the code very carefully.

	The following program writes a greeting 'Hello World' to standard 
	output. It prompts the user for first name and age, reads the info 
	from standard input and prints the information on standard output.
	Pay special attention to library functions printf() and scanf().

	Also note the function declaration, definition, and invocation for 
	years2hours().

	Now terminate this comment with
*/

#include <stdio.h>
#include <stdlib.h>
#define NAMELN 25

int
main()
{
	int age, hours;
	char name [NAMELN];
	int years2hours(int);

	printf("\n Hello World!\n");
	printf("Enter your first name (non-blank characters), followed by age(in years): ");
	scanf("%s %d", name, &age);

	hours = years2hours(age);
	printf("I %s, am %d years = %d hours old\n", name, age, hours);
	printf("Which is %x years in Hex and also %o years in Octal\n", age, age);
	printf("Now I can compile and run a C program!!\n\n");

	exit(0);
}

/* The function converts years given yrs to corresponding hours,
   the result is returned to the caller function.
*/

int
years2hours(int yrs)
{
	int hours = 24, days = 365;
	
	if(yrs > 0)
		return yrs * days * hours;
	else return 0;
}

