.DEFAULT_GOAL := runclean

CC = /usr/local/versionthree/tools/bin/i686-elf-gcc
CFLAGS = -ffreestanding -O2 -Wall -Wextra -nostdlib -static-libgcc -lgcc -I../../include/kernel -I../../include/libc -g

ASM = /usr/local/versionthree/tools/bin/i686-elf-as
AFLAGS =

GRUB_RESCUE = /usr/local/versionthree/tools/bin/grub-mkrescue
EMU = qemu-system-x86_64

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
	$(GRUB_RESCUE) -o versionthree.iso iso

run: versionthree.iso
	$(EMU) -d cpu_reset -device isa-debug-exit,iobase=0xf4,iosize=0x04 -serial stdio -serial file:serial_out.txt -m 4G -cdrom /usr/local/versionthree/versionthree.iso

run-debug: versionthree.iso
	nohup $(EMU) -device isa-debug-exit,iobase=0xf4,iosize=0x04 -serial stdio -serial file:serial_out.txt -m 4G -cdrom /usr/local/versionthree/versionthree.iso -S -s
	wait 2

runclean:
	make clean
	make run

cleanlibc:
	rm -f build/libc/*.o

clean:
	rm -f build/*.o
	rm -f build/*.bin
	rm -f versionthree.iso
