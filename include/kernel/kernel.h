#if !defined(KERNEL_INCLUDED)
#define KERNEL_INCLUDED

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "bootstrap.h"
#include "memory.h"
#include "types.h"
#include "terminal.h"
#include "serial.h"

#define kernel_memory_base  0xC0000000

/* Outputs a byte to the specified hardware port */
static inline void outportb( uint32_t port, uint8_t value)
{
    __asm__ __volatile__ ("outb %%al,%%dx"::"d" (port), "a" (value));
}

/* Outputs a word to a port */
static inline void outportw( uint32_t port, uint32_t value)
{
    __asm__ __volatile__ ("outw %%ax,%%dx"::"d" (port), "a" (value));
}

/* gets a byte from a port */
static inline uint8_t inportb( uint32_t port)
{
    uint8_t value;
    __asm__ __volatile__ ("inb %w1,%b0" : "=a"(value) : "d"(port));
    return value;
}

#define bit_is_set( variable, position ) ( ((variable) >> (position)) & 1 )
#define bit_set( variable, position ) ( (variable) | (1 << (position)) )
#define bit_clear( variable, position ) ( (variable) & ~(1 << (position)) )
#define bit_flip( variable, position ) ( (variable) ^ (1 << (position)) )

#endif