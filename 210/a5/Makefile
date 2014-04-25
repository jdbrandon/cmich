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
ASMSRCS = eval1.s eval2.s eval3.s eval4.s eval5.s

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
