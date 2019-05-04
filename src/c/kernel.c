#include "kernel.h"
#include "stdio.h"

void kernel_main( uint32_t multiboot_magic, multiboot_info_t * multiboot_info ) {
	multiboot_initalize( multiboot_magic, multiboot_info );
	term_initalize( );
	serial_initalize( );
	memory_initalize( );

	printf( "Welcome to Version 3.\n" );

    multiboot_test();
    memory_test();
    
	fputs( "Ending now", stderr );
}