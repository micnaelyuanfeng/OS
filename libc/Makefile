#Copyright (C) <2016>  William Taylor Jones <freemicronix@gmail.com>
#
#This program is free software; you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation; either version 2 of the License, or
#(at your option) any later version.
#
#This program is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.
#
#You should have received a copy of the GNU General Public License along
#with this program; if not, write to the Free Software Foundation, Inc.,
#51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.


AFLAGS=-f elf32

CFLAGS?=-O2 -g
CPPFLAGS?=
LDFLAGS?=
LIBS?=

DESTDIR?=
PREFIX?=/usr
EXEC_PREFIX?=$(PREFIX)
INCLUDEDIR?=$(PREFIX)/include
LIBDIR?=$(EXEC_PREFIX)/lib

CFLAGS:=$(CFLAGS) -Wall -Wextra
CPPFLAGS:=$(CPPFLAGS) -D__is_freemicronix_libc -Iinclude
LIBK_CFLAGS:=$(CFLAGS) -ffreestanding -fbuiltin
LIBK_CPPFLAGS:=$(CPPFLAGS) -D__is_freemicronix_kernel

include $(ARCHDIR)/make.config

CFLAGS:=$(CFLAGS) $(ARCH_CFLAGS)
CPFLAGS:=$(CPPFLAGS) $(ARCH_CPPFLAGS)
LIBK_CFLAGS:=$(LIBK_CFLAGS) $(KERNEL_ARCH_CFLAGS)
LIBK_CPFLAGS:=$(LIBK_CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)

FREEOBJS:=\
$(ARCH_FREEOBJS) \
init/__init_libc.o \
stdio/putchar.o \
stdlib/abort.o \
stdlib/abs.o \
stdlib/atoi.o \
stdlib/exit.o \
stdlib/itoa.o \
stdlib/strreverse.o \
stdlib/u64toa.o \
stdlib/uitoa.o \
string/lfind.o \
string/memcmp.o \
string/memcpy.o \
string/memmove.o \
string/memset.o \
string/strcat.o \
string/strchr.o \
string/strcmp.o \
string/strcpy.o \
string/strcspn.o \
string/strlen.o \
string/strncpy.o \
string/strpbrk.o \
string/strspn.o \
string/strstr.o \
string/strtok.o \
string/strtok_r.o \



HOSTEDOBJS:=\
$(ARCH_HOSTEDOBJS) \
stdlib/exit.o \

OBJS:=\
$(FREEOBJS) \
$(HOSTEDOBJS) \

LIBK_OBJS:=$(FREEOBJS:.o=.libk.o)

BINARIES=\
libc.a \
libg.a \
libk.a \
#$(ARCHDIR)/crt0.o $(ARCHDIR)/crti.o $(ARCHDIR)/crtn.o \

all: $(BINARIES)

.PHONY: all clean install install-headers install-libs

libc.a: $(OBJS)
	$(AR) rcs $@ $(OBJS)

libg.a:
	$(AR) rcs $@

libk.a: $(LIBK_OBJS)
	$(AR) rcs $@ $(LIBK_OBJS)

%.o: %.c
	$(CC) -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

%.o: %.asm
	$(AS) $(AFLAGS) $< -o $@

%.libk.o: %.c
	$(CC) -c $< -o $@ -std=gnu11 $(LIBK_CFLAGS) $(LIBK_CPPFLAGS)

%.libk.o: %.S
	$(CC) -c $< -o $@ $(LIBK_CFLAGS) $(LIBK_CPPFLAGS)

clean:
	rm -f $(BINARIES) $(OBJS) $(LIBK_OBJS) *.o */*.o */*/*.o

install: install-headers install-libs

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -RTv include $(DESTDIR)$(INCLUDEDIR)

install-libs: $(BINARIES)
	mkdir -p $(DESTDIR)$(LIBDIR)
	cp $(BINARIES) $(DESTDIR)$(LIBDIR)