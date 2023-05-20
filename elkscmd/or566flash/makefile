ELKS	= ../..
BASEDIR	= ../
include $(BASEDIR)/Make.defs
include $(BASEDIR)/Make.rules

# Install destination
DESTDIR		= $(TOPDIR)/target
ELKS_LIB86	= $(ELKS)/elks/arch/i86/lib/

NAME	= flash

OUT	= $(NAME)
OBJS	+= main.o flash.o commands.o crc.o protocol.o serial.o

all: $(OUT)

$(OUT):	$(OBJS)
	echo '[LD]	$@'
	$(LD) $(LDFLAGS) -o $@ $^

distclean: clean
	$(RM) *~ $(OUT)

clean::
	$(RM) $(OBJS)

install: $(OUT)
	cp $(OUT) ../sh_utils
