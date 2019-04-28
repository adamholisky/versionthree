#include "kernel.h"
 
void kernel_main(void) 
{
	/* Initialize terminal interface */
	terminal_initialize();
 
	/* Newline support is left as an exercise. */
	terminal_writestring("Hello, higher half world!");

	initalize_serial();

	serial_write( 'a' );
}