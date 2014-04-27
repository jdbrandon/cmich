CFLAGS  = -g -Wall -Werror
LDFLAGS = -lpthread -lrt
CC      = gcc
LD      = gcc

TARG = prodcons
OBJS = a10.o

$(TARG): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(TARG)

clean:
	rm -f *.o *.log $(TARG)

print:
	pr -l60 Makefile $(ASMSRCS) | lpr
#           ^ is lowercase L

