/*	eval3 takes two integers for parameters, the first to be used 
	as a base stored in %i0, and the 2nd to behave as an exponent
	stored in %i1. The function should return the base taken to 
	the exponent. To calculate this the function uses %l0 as a 
	counter variable and sets %o0 to 1, and then in a loop from 1 
	to (exponent-1), multiplies %o0 by the base (%i0). Going from
	1 to (exponent-1) does produce an off by one error in this 
	code, but because the assignment said to copy the given code
	the issue is not fixed and this functions returns base taken 
	to (exponent-1). To execute the loop the function compares 
	%l0 to %i1 (the exponent) and once the value of %l0 is no 
	longer less than %i1, the function exits the loop, clears
	%o0 and returns and restores control to the caller function.
	inside the loop, %o0 (holds what needs to be multiplied by
	the base next and eventually the resulting power) is 
	multipled by %o1 ( which holds the base). Then %l0 is 
	incremented and then the function branches back to loop.
 */

	.global eval3
eval3:	save %sp,-64,%sp
	mov 1,%l0
	mov 1,%o0
loop3:	mov %i0,%o1
	cmp %l0,%i1
	be done3	
	nop
	call .mul
	nop
	inc %l0
	ba loop3
	nop
done3:	mov %o0,%i0
	clr %o0
	ret 
	restore
