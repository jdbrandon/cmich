/* 	This function copys the contents of one string to another
	string. The address of the destination string is passed as
	a parameter in %o0 and the address of the source string is
	found in %o1. In this module, %o2 is used as a counter 
	variable to manipulate the address being loaded from and 
	being stored to. The contents of the address for source plus
	%o2 are loaded into %o3, as long as %03 is not equal to 0, its
	value is saved to the adress in %o0 plus %o2. This 
	effectively coppys the contents of the source string to the
	destination string.
	
 */
	.global stringcpy

stringcpy:	save %sp,-64,%sp
		mov 0,%o5
loop:		ldsb[%i1+%o5],%o2
		cmp %o2,0
		be done
		nop
		stsb %o2,[%i0+%o5]
		inc %o5
		ba loop
		nop
done:		stsb %g0,[%i0+%o5]
		ret
		restore
