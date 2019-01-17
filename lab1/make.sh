#!/bin/bash

as86 -o bs.o  bs.s
bcc -c -ansi  t.c
ld86 -d bs.o t.o /usr/lib/bcc/libc.a

FILENAME=a.out
FILESIZE=$(stat -c%s "$FILENAME")

dd if=a.out of=mtximage bs=1024 count=1 conv=notrunc
qemu-system-i386 -fda mtximage -no-fd-bootchk
 

