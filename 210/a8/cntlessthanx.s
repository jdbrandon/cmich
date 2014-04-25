/*	cntlessthanx is designed to take an array of integers, an int 
	designating the size of the array, and an int that acts as an 
	upper bound on the desired count of numbers as parameters in
	%o0, %o1, and %o2 respectively. Then the function returns the
	number of integers in the array that are less than the value 
	passed in %o2. To accomplish this, the function sets %o4, %o5
	and %g1 to 0 to be used as counter variables. %o4 is used to 
	access the next integer in the array and will be incremnted in
	multiples of 4. %o5 counts iterations of the loop, and %g1 is 
	used to count of numbers in the array that are less than the 
	value passed in %o2. The value in (%o0+%o4) is loaded into %o3
	which is used as a holder variable for the integer values from
	the array. Then %o3 is compared to %o2. If %o3 is less than %o2, 
	then the count in %g1 is incremented, otherwise only %o4 is 
	incremented by 4 and %o5 is incremented by 1(which happens 
	weather or not %o3 is less than %o2) and then the function 
	branches back to loop to load the next value from the array and 
	the process repeats. When %o5 equals %o1, the function branches 
	to done, where the count in %g1 is moved to %o0 to be returned 
	before restoring control to the calling function. The output 
	parameter is the number of values in the array that are smaller 
	than the parameter passed in %o2.
 */

	.global cntlessthanx

cntlessthanx:	save %sp, -64, %sp
		clr %o4
		clr %o5
		clr %g1
loop:		cmp %o5,%i1
		bge done
		nop
		ld [%i0+%o4], %o3
		cmp %o3, %i2
		bl increment
		nop
next:		add %o4,4,%o4
		inc %o5
		ba loop
		nop
increment:	inc %g1
		ba next
		nop
done:		mov %g1, %i0
		ret
		restore
