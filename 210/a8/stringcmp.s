/*	This function is designed to compare two strings given as 
	parameters and determine which is greater in ASCII value 
	or of they are the same string. If the string in %o0 is 
	equal to the string in %o1 then the function returns 0, if
	the string in %o0 is greater than the string in %o1, the 
	function returns a positive value, and if the string in %o0
	is smaller than the string in %o1, the function returns 
	a negative value. To accomplish this the function uses %o4 
	as a counter variable and then loads (%o0+%o4) to %o2 
	and loads (%o1+%o4) to %o3. Then the function compares
	%o2 to %o3, if they are equal the function compares %o2 to 
	0 and branches to done if they are equal because the end of 
	both strings has been reached. If %o2 is not equal to 0
	the function branches to next where %o4 is incremented and the 
	function branches back to loop where %o2 and %o3 are loaded with 
	the next values of their string and the comparison continues. 
	If %o2 is not equal to %o3, the function branches to compute
	where the sum of the rest of the caracters in the rest of
	the strings will be added together and stored in %g1 for 
	the first string and %g2 for the 2nd string. Once the
	running totals have been computed, %o3 will be subtracted
	from %o2 and be used as the return value. If the value 
	returned is greater than 0, then the first string is larger,
	if the value returned is 0, then the first string is the same
	as the second string, and if the value is less than 0, then
	the second string is larger than the first.
 */

	.global stringcmp

stringcmp:	save %sp,-64,%sp
		clr %o4
		clr %g1
		clr %g2
loop:		ldub[%i0+%o4],%o2
		ldub[%i1+%o4],%o3
		cmp %o2, %o3
		be equal
		nop
		cmp %o2, 0
		be done
		nop
		cmp %o3, 0
		be done
		nop
compute:	add %o2,%g1,%g1
		add %o3,%g2,%g2
next:		inc %o4
		ba loop
		nop
equal:		cmp %o2, 0
		bne next
		nop
		clr %i0
done:		sub %g1, %g2, %i0
		ret
		restore
