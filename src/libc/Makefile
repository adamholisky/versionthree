SOURCES := $(wildcard *.c)
OBJECTS := $(patsubst %.c, ../../build/libc/%.o, $(SOURCES))

all: $(OBJECTS) ../../build/libc/setjmp.o

../../build/libc/%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

../../build/libc/setjmp.o : setjmp.S 
	$(CC) $(CFLAGS) -c $< -o $@
