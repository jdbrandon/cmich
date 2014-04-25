/* 	cntofmultiplesof8 is designed to take an input of an array
	of integers, and an integer designating size of the array
	passed in %o0 and %o1 respectively. Then the function passes 
	through the array and counts how many integers in the array 
	are multiples of 8. To achieve this, the function uses %o4, 
	%o5, and %g1 as counter variables. %o4 is used to add to the 
	base address of the array to load subsequent values in the 
	array from memory and is therefore incremented by 4 each 
	time. %o5 is used to keep count of iterations through loop 
	and is incremented 1 at a time. %g1 holds the number of 
	multiples of 8 encountered in the array. First, %g1, %o4, and 
	%o5 are initialized to 0 and then the value stored at 
	(%o0+%o4) is loaded to %o2. Then, %o2 is put into an and 
	operation with 0x7 and the result is stored in %o3. Then %o3 
	is compared to 0 and the function branches to next if %o3 is 
	not equal to 0. If %o3 is equal to 0, the function then puts 
	%o2 in to an and operation with 0xff8 and the result is 
	stored in %o3. Now %o3 is compared to 0 and if it is equal 
	this time, the function branches to next. If %o3 is not equal 
	to 0 then %g1 is incremented because the number in %o2 is a 
	multiple of 8. Then the function reaches next, where 4 is 
	added to %o4, and %o5 is incremented before branching to loop. 
	This process repeats until %o5 is equal to %o1, at which point 
	the function will branch to done because each integer in 
	the array has been tested. In done  %g1 is moved to 
	%o0 to be returned as the count of the multiples of 8 
	within the given array of integers. The number of multiples
	of 8 can be found in the return value of the function.
 */

	.global lcntofmultiplesof8

lcntofmultiplesof8:	clr %o4
			clr %o5
			clr %g1
loop:			cmp %o5, %o1
			bge done
			nop
			ld[%o0+%o4], %o2
			and %o2,0x7,%o3
			cmp %o3,0
			bne next
			nop
			and %o2,0xff8,%o3
			cmp %o3,0
			be next
			inc %g1
next:			inc %o5
			add %o4,4,%o4
			ba loop
			nop
done:			mov %g1,%o0
			retl
			nop
