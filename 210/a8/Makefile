##############################################################
# Variables
# -- allows C-source and assembly-source files mix. Again, the 
# -- indented lines start with a TAB(^I) and not spaces..
##############################################################

CFLAGS  = -g -Wall -Werror
LDFLAGS =
CC      = gcc
LD      = gcc

PROG    = driver
CEESRCS = main.c
ASMSRCS = lstringcpy.s lstringcat.s lreversestr.s lstringucase.s   \
	  lstringlcase.s lstringcmp.s lcntofevens.s lfindlargest.s \
	  lcntlessthanx.s lcntofmultiplesof8.s stringcpy.s \
	  stringcat.s reversestr.s stringucase.s stringlcase.s \
	  stringcmp.s cntofevens.s findlargest.s cntlessthanx.s \
	  cntofmultiplesof8.s stringcpy.s

OBJS    = $(addsuffix .o, $(basename $(CEESRCS) .c))  \
	  $(addsuffix .o, $(basename $(ASMSRCS) .c)) 

##############################################################
# Rules for gmake
##############################################################

$(PROG): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(PROG)

%.o: %.c %.s
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o *˜ $(PROG) a.out a1 driver

print:
	pr -l60 Makefile $(ASMSRCS) | lpr
#           ^ is lowercase L

##########################################################
# Dependencies -- none in this program
##########################################################
