/*	cntofevens is designed to find the count of even 
	numbers in a list of integer values passed in %o0 with
	size n, which is passed in %o1. To achieve this the 
	function uses %g1, %o4, and %o5 as counter variables. 
	The function loads the value of (%o0+%o4) into %o2. Then 
	%o2 is put into an and operation with 1,  and the result
	is stored in %o2. If %o2 equals 0 then the value of %g1 is 
	increased and acts as a count of the even numbers. If %o2 
	does not equal 0, %g1 is not incremented and 4 is added to 
	%o4, %o5 is incremented by one (%o4 and %o5 are incremented 
	regarless of %o2 equaling 0 or not) and the process repeats 
	until %o5 is equal to %o1, at which the function will branch 
	to done, where %g1 is moved to %o0 an control is returned 
	to the calling function where the count of even numbers in 
	the list can be found in the return value.
 */

	.global lcntofevens

lcntofevens:	clr %g1
		clr %o4
		clr %o5
loop:		cmp %o5,%o1
		bge done
		nop
		ld [%o0+%o4], %o2
		and %o2,1,%o2
		cmp %o2, 0
		bne next
		nop
count:		inc %g1
next:		add %o4, 4, %o4
		inc %o5
		ba loop
		nop
done:		mov %g1,%o0
		retl
		nop
