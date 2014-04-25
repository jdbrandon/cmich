/*	This function is designed to take an input string and 
	return that string in reverse order. To do this, the 
	function first uses %o4 and %o5 as counter variables, %o4 is
	incrimented as bits of the string are loaded into %o2
	until the loaded value is 0. At this point %o4 is 
	decreased and now (%o0+%04)represents the address of
	the last character in the string. Now the function
	loads the first character at (%o0+%o5) and the last 
	character at (%o0+%o4) into %o2 and %o3 respectively
	and then stores %o3 in the location of the first
	character and %o2 in the location of the last character.
	Then %o4 is decreased and %o5 is incremented and the 
	process repeats until %o4 equals %o5 or %o4 is less than
	%o5. After this process completes, the input string has
	been revered and the function restores control to the
	calling function where the input parameter now contains
	the string in reverse order.
 */

	.global reversestr

reversestr:	save %sp, -64, %sp
		clr %o4
		clr %o5
endofstr:	ldub [%i0+%o4], %o2
		cmp %o2,0
		be next
		nop
		inc %o4
		ba endofstr
		nop
next:		cmp %o4, %o5
		ble done
		nop
		dec %o4
		ldub [%i0+%o4], %o2
		ldub [%i0+%o5], %o3
		stb %o3, [%i0+%o4]
		stb %o2, [%i0+%o5]
		inc %o5
		ba next
		nop
done:		ret
		restore
