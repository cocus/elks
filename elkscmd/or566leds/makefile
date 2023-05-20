BASEDIR=..

include $(BASEDIR)/Make.defs

###############################################################################
#
# Include standard packaging commands.

include $(BASEDIR)/Make.rules

HOSTCC = gcc
HOST_CFLAGS = -O2
KERNEL_LIBS = $(TOPDIR)/elks/arch/i86/lib/lib86.a

###############################################################################

PRGS = leds pcbi 8018x-mem

#PRGS_HOST=compress.host

all: $(PRGS) $(PRGS_HOST)

leds: leds.o
	$(LD) $(LDFLAGS) -o leds leds.o $(LDLIBS)

pcbi: pcbi.o
	$(LD) $(LDFLAGS) -o pcbi pcbi.o $(LDLIBS)

8018x-mem: 8018x-mem.o
	$(LD) $(LDFLAGS) -o 8018x-mem 8018x-mem.o $(LDLIBS)

compress.host: compress.c
	$(HOSTCC) $(HOST_CFLAGS) -s compress.c -o $@

install: $(PRGS)
	$(INSTALL) $(PRGS) $(DESTDIR)/bin

clean:
	rm -f $(PRGS) $(PRGS_HOST) *~ *.o
