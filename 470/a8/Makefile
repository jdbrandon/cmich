##############################################################
# Variables
# -- allows C-source and assembly-source files mix. Again, the 
# -- indented lines start with a TAB(^I) and not spaces..
##############################################################

CFLAGS  = -g -Wall -Werror
LDFLAGS = -lpthread -lrt
CC      = gcc
LD      = gcc

TARG1 = psrpipe
OBJS1 = psr1.o
TARG2 = psrmutex
OBJS2 = psr2.o
TARG3 = psrsem
OBJS3 = psr3.o 

all = $(TARG1) $(TARG2) $(TARG3)

all: $(TARG1) $(TARG2) $(TARG3)

$(TARG1): $(OBJS1)
	$(LD) $(LDFLAGS) $(OBJS1) -o $(TARG1)


$(TARG2): $(OBJS2)
	$(LD) $(LDFLAGS) $(OBJS2) -o $(TARG2)


$(TARG3): $(OBJS3)
	$(LD) $(LDFLAGS) $(OBJS3) -o $(TARG3)

clean:
	rm -f *.o  a.out $(all)

print:
	pr -l60 Makefile $(ASMSRCS) | lpr
#           ^ is lowercase L

