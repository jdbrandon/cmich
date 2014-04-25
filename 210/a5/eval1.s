/* 	eval1 performs the factorial function (n! = n*(n-1)*...*2*1)
	to do this the eval1 function takes the parameter in %i0  
	passed and moves it to %o0. Here %o0 is compared to 0 and if 
	it is equal it branches to case01 where 1 is moved to %o0 
	because by definition, 0! = 1. If %o0 is not initially equal to 0,
	%l1 is assigned "%o0-1" and %l1 is assigned to %o1. Then the 
	.mul function is called and %l1 is decresed in a loop as long 
	as %l1 is not equal to 1. %l1 is used as a counter, counting 
	down. This performs the factorial function on %o0 exept for 
	the final "*1" identity multiplication which has no affect on the 
	result. Once %l1 equals 1, it branches to done1 where %o0 is 
	moved to %i0 and %o0 is cleared before returning control to the 
	caller function. During calculation %o0 holds the input value 
	and then the multipucation so far, until at the end of the 
	loop it holds the desired return value. %o1 gets the next 
	value to multiply by which is the counter value stored in
	%l1. The output for this function is the factorial relation
	on the input.
 */
	.global eval1
eval1: 	save %sp, -64, %sp
	mov %i0,%o0
	cmp %o0,0
	be case01
	nop
	sub %o0,1,%l1
loop1:	cmp %l1,1
	be done1
	nop
	mov %l1,%o1
	call .mul
	nop
	dec %l1
	ba loop1
	nop
case01:	mov 1,%o0
done1: 	mov %o0,%i0
	clr %o0
	ret
	restore
