/* 	This function is designed to take a string of characters
	and make all of the lowercase characters uppercase and 
	leave the uppercase characters alone. To do this, the 
	function uses %o4 as a counter variable so it is initially
	set to 0. Then the function loads the value at (%o0+%o4)
	which first value in to %o2. Then the function compares 
	%o2 to 'z' and if %o2 is less than 'z' then the function
	compares %o2 to 'a' and if %o2 is greater than 'a' then
	the function subtracts 's' from %o2 and then adds 'A' to
	%o2 to convert the value in to %o2 to uppercase from
	lowercase. Then the value in %o2 is stored in the address 
	it came from (%o0+%o4). If the value in %o2 is greater than 
	'z' or less than 'a' the function branches to next, where
	%o4 is incremented and then branches to loop where the process
	repeats until the value loaded to %o2 is 0, marking the end
	of the string. At this point the function branches to done
	where the function returns control to the caller function 
	which can then find the uppercase string in the parameter
	passed to the stringucase function.
 */

	.global lstringucase

lstringucase:	clr %o4
loop:		ldub [%o0+%o4], %o2
		cmp %o2, 0
		be done
		nop
		cmp %o2, 'z'
		ble testlcase
		nop
		ba next
testlcase:	cmp %o2, 'a'
		bl next
		nop
		sub %o2,'a',%o2
		add %o2,'A',%o2
		stb %o2, [%o0+%o4]
next:		inc %o4
		ba loop
		nop
done:		retl
		nop
