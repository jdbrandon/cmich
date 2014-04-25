/*	The function findlargest, given a list of integers passed 
	in %o0 and a size n passed in %o1, is designed to return the 
	largest value in the list of integers. To accomplish
	this, %o4 and %o5 are used as counter variables. %o4 is used 
	to access memory loactions of subsequent integers in the list
	and is incremented by 4 each time, %o5 is a counter of 
	iterations and is incremented by 1 at a time. First the 
	function sets %o4 and %o5 to 0 then it loads the value at
	(%o0+%o4) into %o2 which is used as a holder of values from
	the input array. If the count in %o4 is 0, the loaded 
	value is placed in %o3 which holds the current maximum. If 
	%o4 is greater than 0, then %o2 is compared to %o3 and if
	%o2 is greater than %o3, the value in %o2 is moved to %o3,
	then %o4 is incremented by 4, %o5 is incremented by one, 
	and the next int value is loaded within loop. This process 
	repeats until %o5 is equal to %o1. At the end of this process
	the maximum is found in %o3 which is then moved to %o0
	before returning conrol to the calling function which will
	have the largest value in the passed list of integers in 
	the return value.
 */

	.global findlargest

findlargest:	save %sp, -64, %sp
		clr %o4
		clr %o5
loop:		cmp %o5,%i1
		bge done
		nop
		ld [%i0+%o4], %o2
		cmp %o4,0
		be initialval
		nop
		cmp %o2,%o3
		ble next
		nop
		mov %o2, %o3
		ba next
		nop
initialval:	mov %o2, %o3
next:		add %o4,4,%o4
		inc %o5
		ba loop
		nop
done:		mov %o3, %i0
		ret
		restore
