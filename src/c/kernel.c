#include "kernel.h"
#include "stdio.h"
 
void kernel_main(void) 
{
	/* Initialize terminal interface */
	terminal_initialize();
	initalize_serial();
 
	/* Newline support is left as an exercise. */
	printf( "Hello, %s world!", "printf()" );
	
	fputs( "And hello serial world...", stderr );
}