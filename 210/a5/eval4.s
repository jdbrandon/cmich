/*	eval4 determines if the given parameter is a perfect number
	which means that the sum of the numbers that evenly divide it 
	add to that number. If the parameter is a perfect number then
	1 is returned, otherwise 0 is returned. To accomlish this, 
	%l1 is initially cleared to be used as a sum. Then the 
	input parameter value is moved to %l0. Then %l2 is set to 0 
	so it can be incremented in the loop and start at a value of 1
	inside the loop. here %l2 is compared to %l0, the parameter,
	and if it is greater than %l0, then the function branches to
	false and returns 0. if %l2 is less than %l0, %l2 is moved to 
	%o1, %l0 is moved to %o0 and the remainder function is called. 
	Then %o0 is compared to 0. If the remainder (%o0) is 0, then 
	%l2 (the divisor) is added to the sum (%l1), which is stored 
	in %l1, and then branches back to the begnning of loop. If the 
	remainder is not equal then the function branches to loop
	with out adding %l2 to %l1. If in loop the comparison of
	%o1 and %l0 are equal, the function branches to check4 where
	it is determined if the sum is equal to the given parameter
	by comparing %l1 to %l0. If they are not equal the function 
	branches to false4. If they are equal, 1 is moved to %i0 
	before branching to done4 where 1 will be returned. 
 */
	.global eval4

eval4:	save %sp,-64,%sp
	clr %l1
	mov %i0,%l0
	mov 0,%l2
loop4:	inc %l2
	cmp %l2,%l0
	be check4
	nop
	bg false4
	nop
	mov %l2,%o1
	mov %l0,%o0
	call .rem
	nop
	cmp %o0,0
	bne loop4
	nop 	
	add %l2,%l1,%l1
	ba loop4
	nop
check4:	cmp %l1,%l0
	bne false4
	nop
	mov 1,%i0
	ba done4
	nop
false4:	mov 0,%i0
done4:	clr %o0
	ret
	restore
