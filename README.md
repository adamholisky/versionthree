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
Git clone into /versionthree (must be on root of drive, otherwise modify paths).

Create directories:
  * /versionthree/tools
  * /versionthree/tools/bin
  * /versionthree/tools/build
  * /versionthree/tools/originals
  * /versionthree/tools/src

Download into /versionthree/tools/original:
  * https://ftp.gnu.org/gnu/gcc/gcc-8.3.0/gcc-8.3.0.tar.gz
  * https://ftp.gnu.org/gnu/binutils/binutils-2.32.tar.gz
  * https://ftp.gnu.org/gnu/mpc/mpc-1.1.0.tar.gz
  * https://ftp.gnu.org/gnu/mpfr/mpfr-4.0.2.tar.gz
  * https://ftp.gnu.org/gnu/gmp/gmp-6.1.2.tar.xz
  * https://www.nasm.us/pub/nasm/releasebuilds/2.14.02/nasm-2.14.02.tar.gz 
  * ftp://ftp.gnu.org/gnu/grub/grub-2.02.tar.gz

Extract to /versionthree/tools/src directory.

Remove versions from all folders in /versionthree/tools/src directory.

Move MPC, MPFR, GMP folders in to GCC folder

Add to ~/.bash_profile:
  * export PATH="/versionthree/tools/bin:$PATH"

cd /versionthree/tools/build
rm -rf *
../src/binutils/configure --prefix=/versionthree/tools --target=i686-elf --enable-interwork --enable-multilib --disable-nls --disable-werror && make && make install

cd /versionthree/tools/build
rm -rf *
../src/gcc/configure --target=i686-elf --prefix=/versionthree/tools --disable-nls --enable-languages=c --without-headers
make all-gcc && make all-target-libgcc && make install-gcc && make install-target-libgcc

cd /versionthree/tools/build
rm -rf *
../src/nasm/configure --prefix=/versionthree/tools 
make && make install


Components
=====

Libc
-----
https://sourceware.org/newlib/

Terminal
-----
Support [ANSI escpe codes(https://en.wikipedia.org/wiki/ANSI_escape_code)]

