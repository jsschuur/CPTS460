#!/bin/bash

as86 -o bs.o  bs.s
bcc -c -ansi  t1.c
ld86 -d bs.o t1.o /usr/lib/bcc/libc.a

FILENAME=a.out
FILESIZE=$(stat -c%s "$FILENAME")

dd if=a.out of=mtximage bs=1024 count=1 conv=notrunc
qemu-system-i386 -fda mtximage -no-fd-bootchk
 

