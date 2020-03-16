.DEFAULT_GOAL := runclean

CC = /Users/adam/versionthree/tools/bin/i686-elf-gcc
CFLAGS = -ffreestanding -O2 -Wall -Wextra -nostdlib -static-libgcc -lgcc -I../../include/kernel -I../../include/libc -g

ASM = /Users/adam/versionthree/tools/bin/i686-elf-as
AFLAGS =

#GRUB_RESCUE = /Users/adam/versionthree/tools/bin/grub-mkrescue
GRUB_RESCUE = /usr/local/Cellar/i386-elf-grub/2.04/bin/i386-elf-grub-mkrescue
EMU = /Users/adam/versionthree/tools/bin/qemu-system-i386

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
	$(GRUB_RESCUE) --xorriso=/Users/adam/versionthree/tools/bin/xorriso -o versionthree.iso iso

run: versionthree.iso
	$(EMU) -d cpu_reset -device isa-debug-exit,iobase=0xf4,iosize=0x04 -serial stdio -serial file:serial_out.txt -m 4G -cdrom /Users/adam/versionthree/versionthree.iso

run-debug: versionthree.iso
	nohup $(EMU) -device isa-debug-exit,iobase=0xf4,iosize=0x04 -serial stdio -serial file:serial_out.txt -m 4G -cdrom /Users/adam/versionthree/versionthree.iso -S -s
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
