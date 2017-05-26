##############################################################################
# GNU Makefile for windows benchmark tool wtime.exe
# /TR 2017-05-19
##############################################################################

# mingw
CROSS32	= i686-w64-mingw32-
CROSS64	= x86_64-w64-mingw32-

CC	= gcc
STRIP	= strip
SFLAGS	= -R .note -R .comment

CFLAGS	= -W -Wall -pipe -Wno-format
CFLAGS	+= -fomit-frame-pointer
CFLAGS	+= -O3
#CFLAGS	+= -flto
#CFLAGS += -march=native
LDFLAGS	= -lwinmm -lpsapi

PRGS	= wtime-w64.exe wtime-w32.exe
OBJS	= wtime.c

all:	again
again:	clean $(PRGS)

wtime-w64.exe:
	$(CROSS64)$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)
	$(CROSS64)$(STRIP) $(SFLAGS) $@

wtime-w32.exe:
	$(CROSS32)$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)
	$(CROSS32)$(STRIP) $(SFLAGS) $@

clean:
	rm -f $(PRGS)
