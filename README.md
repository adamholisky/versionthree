# versionthree
Version Three of my hobby OS

Roadmap
=====

* Build tools on Mac
* Grub bootload into asm
* ASM setups kernel to upper half
* Enter C environment
* Serial output
  * k_putchar_serial( port, char )
  * k_puts_serial( port, const char *str )
* Setup Streams
  * stdin <-- Keyboard
  * stdout <-- Terminal
  * stderr <-- Serial
* Basic output:
  * int k_putc( int char, FILE *stream )
  * int k_putchar( int char )
  * k_puts( const char *str )
  * stand alone k_printf()?
* Interrupts
* Basic Keyboard handler
* Basic Input:
  * int k_getc( FILE *stream )
  * int k_getchar( void )
  * char *k_gets( char *str )
* Basic terminal
  * Tokenize input
  * Quick and dirty command routing
* Memory Manager
* Process
* Threads
* newlibc


Build Instructions
=====
.


Components
=====

Libc
-----
https://sourceware.org/newlib/

Terminal
-----
Support [ANSI escpe codes(https://en.wikipedia.org/wiki/ANSI_escape_code)]

