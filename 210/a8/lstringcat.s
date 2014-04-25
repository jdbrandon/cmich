/* 	This module is supposed to take two strings as parameters
	(found in %o0 and %o1) and concatonate them, specifically
	the string from %o1 and add it to the end of the string in
	%o0. To do this, %o4 and %o5 are used as a counter variables
	and the function loads the bits of the string in %o0 into %o2 
	and compare them to 0 and increment %o0 as long is it is not 
	equal to 0. Once the address containing 0 (the end of string 
	marker) the function loads the bits of the string in %o1 to %o3, 
	and stores them in the address at %o0 and then increments %o0 
	and %o1 and repeats until the byte loaded form %o1 is equal to 0. 
	Then the function branches to done where 0 is stored in the next 
	address in %o0 so the new string has an end of string marker.
	Then the function returns control to the calling function where
	a concatonated string can be found in the destination string.
 */

	.global lstringcat

lstringcat:	clr %o4
		clr %o5
endofdst:	ldub [%o0+%o4], %o2
		cmp %o2, 0
		be next
		nop
		inc %o4
		ba endofdst
		nop
next:		ldub [%o1+%o5], %o3
		cmp %o3, 0
		be done
		nop
		stb %o3, [%o0+%o4]
		inc %o4
		inc %o5
		ba next
		nop
done:		inc %o4
		stb %g0, [%o0+%o4]
		retl
		nop
