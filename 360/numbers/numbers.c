#include <stdio.h>
#include<stdlib.h>

int main(){
	int sum,count,neg,odd,number;
	sum=count=neg=odd=0;
	printf("Enter in space separated numbers.\nEnter a non numeric character to stop.\n");
	while(scanf("%d",&number)==1){
		count++;
		sum+=number;
		if(number<0){
			neg++;
		}
		if(number & 1)odd++;
	}

	printf("\n%d Numbers\nSum: %d\n%d negative\n%d odd\n",count,sum,neg,odd);
	exit(0);
}
