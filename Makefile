.DEFAULT_GOAL := runclean

CC = /versionthree/tools/bin/i686-elf-gcc
CFLAGS = -ffreestanding -O2 -Wall -Wextra -nostdlib -static-libgcc -lgcc -I../../include

ASM = /versionthree/tools/bin/i686-elf-as
AFLAGS =

export

all: versionthree.iso

versionthree.iso:
	$(MAKE) -C src/asm
	$(MAKE) -C src/c
	$(MAKE) -C src/devices
	$(MAKE) -C src/support
	cp -f build/versionthree.bin iso/boot/versionthree.bin
	grub-mkrescue -o versionthree.iso iso

run: versionthree.iso
	qemu-system-i386 -device isa-debug-exit,iobase=0xf4,iosize=0x04 -cdrom versionthree.iso -serial stdio -serial file:serial_out.txt -m 4G

runclean:
	make clean
	make run

clean:
	rm -f build/*.o
	rm -f build/*.bin
	rm -f versionthree.iso
