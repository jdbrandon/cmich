##############################################################
# Variables
# -- allows C-source and assembly-source files mix. Again, the 
# -- indented lines start with a TAB(^I) and not spaces..
##############################################################

CFLAGS  = -g -Wall -Werror
LDFLAGS =
CC      = gcc
LD      = gcc

TARG    = driver
OBJS 	= a1.o

$(TARG): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(TARG)

clean:
	rm -f *.o *˜ $(PROG) a.out a1 driver

print:
	pr -l60 Makefile $(CEESRCS) | lpr
#           ^ is lowercase L
