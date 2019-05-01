# versionthree
Version Three of my hobby OS

Roadmap
=====

* Build tools on Mac / Windows - DONE
* Grub bootload into asm - DONE
* ASM setups kernel to upper half - DONE
* Enter C environment - DONE
* Serial output - DONE
  * k_putchar_serial( port, char )
  * k_puts_serial( port, const char *str )
* Setup Streams
  * stdin <-- Keyboard
  * stdout <-- Terminal
  * stderr <-- Serial
* Basic output: - DONE
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
  * https://ftp.gnu.org/gnu/binutils/binutils-2.32.tar.gz
  * https://ftp.gnu.org/gnu/gcc/gcc-8.3.0/gcc-8.3.0.tar.gz
  * https://ftp.gnu.org/gnu/mpc/mpc-1.1.0.tar.gz
  * https://ftp.gnu.org/gnu/mpfr/mpfr-4.0.2.tar.gz
  * https://ftp.gnu.org/gnu/gmp/gmp-6.1.2.tar.xz
  * https://www.nasm.us/pub/nasm/releasebuilds/2.14.02/nasm-2.14.02.tar.gz 
  * http://www.agner.org/optimize/objconv.zip
  * https://ftp.gnu.org/gnu/grub/grub-2.02.tar.gz
  * https://download.qemu.org/qemu-4.0.0.tar.xz

Extract to /versionthree/tools/src directory.

Unzip objconv's source.zip into the objconv directory.

Remove versions from all folders in /versionthree/tools/src directory.

Move MPC, MPFR, GMP folders in to GCC folder

Add to ~/.bash_profile:
  * export PATH=/versionthree/tools/bin:$PATH

cd /versionthree/tools/build
rm -rf /versionthree/tools/build
../src/binutils/configure --prefix=/versionthree/tools --target=i686-elf --enable-interwork --enable-multilib --disable-nls --disable-werror && make && make install

cd /versionthree/tools/build
rm -rf /versionthree/tools/build
../src/gcc/configure --target=i686-elf --prefix=/versionthree/tools --disable-nls --enable-languages=c --without-headers
make all-gcc && make all-target-libgcc && make install-gcc && make install-target-libgcc

cd /versionthree/tools/build
rm -rf /versionthree/tools/build
../src/nasm/configure --prefix=/versionthree/tools 
make && make install

cd /versionthree/tools/build
rm -rf /versionthree/tools/build
g++ -o objconv -O2 ../src/objconv/source/*.cpp --prefix=/versionthree/tools
cp objconv /versionthree/tools/bin

cd /versionthree/tools/build
rm -rf /versionthree/tools/build
../src/grub/configure --disable-werror TARGET_CC=i386-elf-gcc TARGET_OBJCOPY=i386-elf-objcopy TARGET_STRIP=i386-elf-strip TARGET_NM=i386-elf-nm TARGET_RANLIB=i386-elf-ranlib --target=i386-elf --prefix=/versionthree/tools
make && make install

cd /versionthree/tools/build
rm -rf /versionthree/tools/build
brew install pkg-config 
brew install glib
brew install pixman
../src/qemu/configure --prefix=/versionthree/tools --target-list=i386-softmmu,x86_64-softmmu

QEMU Changes for Mac:
in ui/cocoa.m
  * Add: [NSApp activateIgnoringOtherApps:YES]; after the conditional code block for "if fullscreen mode is to be used"
  * In the verifyQuit function, comment out existing code, replace with: return YES;
These will force the emulator to the front after it's run as part of the build process, and not show a quit confirmation dialog


cd /versionthree/tools/src/xorriso
./configure --prefix=/versionthree/tools
make && make install

Components
=====

Libc
-----
https://sourceware.org/newlib/

Terminal
-----
Support [ANSI escpe codes(https://en.wikipedia.org/wiki/ANSI_escape_code)]

