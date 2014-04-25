/*	Name: Jeff Brandon,		Class: cps210
  	Section: 22169660		Assignment: 02
   	Due Date: January 25, 2012 	Started: January 20, 2012
   	Credit: 20 points .
	
	Problem: Write a program that can determine the maximum,
	minimum, average, and median values from an array of integers.
	The program will determine the location of the maximum and 
	minimum values in the array and assign those values to their
	respective variables. Then the array will be sorted using
	selection sort to calculate the median, which once calulated
	is assigned to its respective variable. Lastly, the sorted 
	array is printed to standard output, 6 integers per row, with 
	10 collumns for each and then the largest, smallest, average,
	and median values are reported.
	
	Solution: Find max, min, average, and median values using functions

	Data-structure used: 1D int array.

 */

#include <stdio.h>
#include <stdlib.h>
#define SIZE 22

int main()
{
	int average(int[], int), maxpos(int[], int, int);
	int median(int[], int), minpos(int[], int, int);
	int printdata(), printresults();
	int data[SIZE] = {1, 2, 3, -3, -99, 999, 42, 14, 56, 76, 99, 12,
                        -2345, 3456789, 199, 123, 234, -567, -999, 21, 32,
                        -12345};
	int avg, max, maxloc, medianval, min, minloc, size;

	size=SIZE;
	
	if (size > 0) {
		
                maxloc = maxpos(data, 0, size-1);
		max = data[maxloc];
		minloc = minpos(data, 0, size-1);
		min = data[minloc];
		avg = average(data, size);
		medianval = median(data, size);
		printdata(data, size);
		printresults(max, min, avg, medianval);
        }
	exit(0);
}
