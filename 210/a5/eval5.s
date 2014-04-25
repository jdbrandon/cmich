/* 	eval5 computes and returns the greatest common divisor of two 
	input parameters of type integer.To do this computation %l0 
	and %l1 are used as temporary variables. If the input 
	parameters are both zero, -1 is returned, if the second 
	integer is zero then the first integer  is returned. Then 
	after these initial checks, the value of the second 
	parameter(%i1) is passed to %l1. Then in a loop %i1 is 
	assigned the value of %l1, %l0 is assigned the value of %i0
	(mod) %i1.(to do this the values of %i0 and %i1 are passed to 
	%o0 and %o1 respectively before calling the .rem function and then 
	storing the result in %l0), then the value of %i1 is assigned
	to %i0 and %l1 is assigned the value of %l0. As long as %l0
	is not equal to zero, th loop continues. Once %l0 is equal to
	zero, the loop is exited and %i1 is moved to %i0 to be 
	returned before returning the value and restoring control to 
	the caller function. The return parameter is the largest
	interger that divides both of the input parameters.
 */

		.global eval5
eval5: 		save %sp,-64,%sp
		cmp %i1,0
		be casez5
		nop
		mov %i1,%l1
loop5:		mov %l1,%i1
		mov %i0,%o0
		mov %i1,%o1
		call .rem
		nop
		mov %o0,%l0
		mov %i1,%i0
		mov %l0,%l1
		cmp %l0,0
		bne loop5
		nop
		mov %i1,%i0
		ba done5
		nop
casez5:		cmp %i0,0
		be casebz5
		nop
		ba done5
		nop
casebz5:	mov -1,%i0
done5:		clr %o0
		ret	 
		restore

