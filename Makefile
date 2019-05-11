.DEFAULT_GOAL := runclean

CC = /versionthree/tools/bin/i686-elf-gcc
CFLAGS = -ffreestanding -O2 -Wall -Wextra -nostdlib -static-libgcc -lgcc -I../../include/kernel -I../../include/libc

ASM = /versionthree/tools/bin/i686-elf-as
AFLAGS =

# This will get things working on VSCode and WSL, but should leave other *nixs alone
ifndef DISPLAY
DISPLAY=:0
endif

export

#we're leaving libc seperate since it's not changing and is a stop-gap until porting newlib over
libc:
	$(MAKE) -C src/libc

all: versionthree.iso

versionthree.iso:
	$(MAKE) -C src/asm
	$(MAKE) -C src/c
	$(MAKE) -C src/devices
	$(MAKE) -C src/support
	cp -f build/versionthree.bin iso/boot/versionthree.bin
	grub-mkrescue -o versionthree.iso iso

run: versionthree.iso
	qemu-system-i386 -device isa-debug-exit,iobase=0xf4,iosize=0x04 -cdrom versionthree.iso -serial stdio -serial file:serial_out.txt -m 4G -nic user,ipv6=off,model=e1000,mac=52:54:98:76:54:32 -usb

runclean:
	make clean
	make run

cleanlibc:
	rm -f build/libc/*.o

clean:
	rm -f build/*.o
	rm -f build/*.bin
	rm -f versionthree.iso
