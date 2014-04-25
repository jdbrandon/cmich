#include <stdio.h>
#include <stdlib.h>

/*	Problem: need to find maximum value in an integer array
	Solution: using arguments find max value by comparing each
	value in an unsorted array.
 */
int maxpos(int d[], int low, int high){
	int i = low;
	int maxpos=0;
	int value =d[0];
	while(i <= high){
		if(value < d[i]){
                	value=d[i];
			maxpos=i;
		}
		i++;
	}
return maxpos;
}


/*	Problem: need to find minimum value in an integer array
	Solution: use arguments to compare relevent values in the
	array to find the minimum value.
 */
int minpos(int d[], int low, int high){
	int i = low;
	int minposition=i;
	int value = d[i];
	while( i <= high){
		if(value > d[i]){
			value = d[i];
			minposition = i;
		}
	i++;
	}
return minposition;
}


/*	Problem: Find average value from an integer array.
	Solution: Sum each value and divide by the size of the array.
 */
int average(int d[], int size){
	int i=0;
	int sum=0;
	int average=0;

	while( i < size){
		sum+=d[i];
		i++;
	}
	average=sum/size;
	return average;
}


/*	Problem: Array needs to be ordered from smallest value to
	highest. 
	Solution: use selection sort and call minpos() to sort the array.
 	only called by median()
 */
void selectsort(int d[], int size){
	int lower=0;
	int higher=(size-1);
	int hold;
	int minimumpos;
	while( lower <= higher ){
		hold = d[lower];
		minimumpos = minpos(d,lower,higher);
		d[lower]=d[minimumpos];
		d[minimumpos]=hold;
		lower++;
	}
}


/*	Problem: need to determine the median value.
	Solution: determines the median value from the data by
   	calling selectsort() for sorting the data set.
	then depending on the size of the array (odd/ even)
	the median is calculated appropriately.
 */
int median(int d[], int size){
	int med;
	int a;
	int b;
	selectsort(d, size);
	if( (size % 2) == 0 ){
		a= size/2;
		b= (size/2)+1;
		med=(d[a-1]+d[b-1])/2;
	}
	else{
		med=d[((size+1)/2)-1];
	}
	return med;
}


/* prints data values 6 per line in 10 collumns
   using a while loop that stops after each entry
   has been printed, using the modular relation
   operation I print a new line every 6th entry
 */
void printdata(int d[], int size){
	int check=6;
	int i=0;
	printf("\nThe following is the integer contents of the array.\n\n ");
	while(i < size){
		if((i % check)==0)
			printf("\n");
		printf("%10d",d[i]);
	i++;	
	}
	printf("\n");
}
/* takes calculations from other modules 
   prints them to the user.
 */
void printresults(int largest, int smallest, int average, int medianval){
	printf("\n\nLargest:%11d\n",largest);
	printf("Smallest:%10d\n",smallest);
	printf("Average:%11d\n",average);
	printf("Median:%12d\n",medianval);
}
