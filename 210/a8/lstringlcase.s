/*	This function is designed to take an input string and 
	convert all uppercase charcters to lowercase characters
	while leaving lowercase characters as they are. To do this
	%o4 is used as a counter variable and initialized to 0.
	then the initial value of the string found at (%o0+%o4)
	is loaded to %o1 and compared to 0. If %o1 is equal to 
	0 marking the end of string, the function branches to 
	done where control is returned to the calling function
	where the all lowecase version of the input string can 
	be found in the parameter passed to stringlcase. If %o1
	is not equal to zero is is compared to 'Z' and if it is 
	less than 'Z' the function branches to test where the 
	function compares %o1 to 'A'. If %o1 is greater than 'Z'
	or less than 'A' the value is not uppercase and the 
	function branches to next where %o4 is incremented and 
	the function branches to loop where the next value of the 
	input string is loaded. If the value is both less than 'Z'
	and greater than 'A' the function subtracts the value of
	'A' from %o1 and then adds the value of 'a' to %o1 which
	converts it to a lowercase version of the letter in %o1
	then %o1 is stored in the address it was found in 
	(%o0+%o4). This repeats until the end of the string is 
	reached and the function branches to done.
 */

	.global lstringlcase

lstringlcase:	clr %o4
loop:		ldub [%o0+%o4], %o1
		cmp %o1, 0
		be done
		nop
		cmp %o1, 'Z'
		bg next
		nop
		cmp %o1, 'A'
		bl next
		nop
		sub %o1,'A', %o1
		add %o1,'a', %o1
		stb %o1,[%o0+%o4]
next:		inc %o4
		ba loop
		nop
done:		retl
		nop
