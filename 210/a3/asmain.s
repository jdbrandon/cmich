/*	5*4= 20-->l0
	2%6= 2-->l1
	8*9= 72-->l2
	7+8= 15-->l3
	2%20= 2--> i2
	9/2= 4-->l1
	72/3= 24-->l2
	15*10=150-->l3
	3-20= -17-->l0
	-17-2= -19-->l0
	-19+24= 5-->l0
	5+150= 155-->l0
 */

	.global main
main:	save %sp, -64, %sp

first:	mov 4, %o0
	mov 5, %o1
	call .mul
	nop
	mov %o0, %l0
	mov 2, %o0
	mov 6, %o1
	call .rem
	nop
	mov %o0, %l1
	mov 8, %o0
	mov 9, %o1
	call .mul
	nop
	mov %o0,%l2
	mov 7, %o0
	add %o0, 8, %l3
	mov 2, %o0
	mov %l0, %o1
	call .rem
	nop
	mov %o0, %i2
	mov 9, %o0
	mov %l1, %o1
	call .div
	nop
	mov %o0, %l1
	mov %l2, %o0
	mov 3, %o1
	call .div
	nop
	mov %o0, %l2
	mov 10, %o0
	mov %l3, %o1
	call .mul
	nop
	mov %o0, %l3
	mov 3, %o0
	sub %o0, %l0, %l0
	sub %l0, %i2, %l0
	sub %l0, %l1, %l0
	add %l0, %l2, %l0
last:	add %l0, %l3, %l0

	clr %o0
	call exit, 0
	nop
