/*	eval2 calculates the sum of squares from 1 to one less 
	than two times the passed parameter 
	((1^2)+(2^2)+...+(((2n)-1)^2)+(2n)^2). To calculate this the 
	function moves %i0 (the input parameter) to %o0, and %l1 is 
	cleared so it can be used to store the sum. Then 2 is moved 
	to %o1 and the .mul function is called to claculate two 
	times the input parameter. the result in %o0 is then moved to 
	%l0. Next 1 is moved to %l2 and then is compared to %l0, if 
	%l2 is less than %l0 then the value of %l2 is moved to %o0, 
	and %o1 the .mul function is called, and the the result is 
	added to %l1 and stored in %l1 in a loop which starts with
	comparing %l2 to %l0 and ends with incrimenting %l2. Once 
	%l2 is no longer smaller than %l0, the loop is not entered
	and the value %l1 is moved to %i0, and %o0 is cleared  before 
	returing control to the caller function. Also if %i0 is 
	greater than %l0 at the initial comparisson then the 
	function branches to neg2 (for the case that %l0 is negative
	or 0) which moves 0 to %l1 before returing. In the loop %o0, 
	and %o1 are assigned the value of %l2 which holds the next 
	value to be squared and added to the sum, %l1.
 */
	.global eval2

eval2: 	save %sp,-64,%sp
	mov %i0,%o0
	clr %l1
	mov 2,%o1
	call .mul
	nop
	mov %o0,%l0
	mov 1,%l2
loop2:	cmp %l2,%l0
	be done2
	nop
	bg neg2
	nop
	mov %l2,%o0
	mov %o0,%o1
	call .mul
	nop
	add %o0,%l1,%l1
	inc %l2
	ba loop2
	nop
neg2:	mov 0,%l1
done2: 	mov %l1,%i0
	clr %o0
	ret
	restore
