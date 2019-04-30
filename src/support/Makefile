OBJECTS := $(wildcard ../../build/*.o) $(wildcard ../../build/libc/*.o)

all:
	$(CC) -T linker.ld -o ../../build/versionthree.bin $(CFLAGS) $(OBJECTS)