#include "kernel.h"
#include "stdio.h"
 
void kernel_main(void) 
{
	term_initalize();
	initalize_serial();
    memory_initalize();
 
	printf( "Welcome to Version 3\n\nNow with multiple lines... oooh!" );
	
	fputs( "Ending now", stderr );
}