#include "kernel.h"

void * k_malloc_head;

void memory_initalize( void ) {
	k_malloc_head = ( void * )( 0xCB000000 );

	memory_test( );
}

void * k_malloc( uint32_t size ) {
	void * return_val = k_malloc_head;

	k_malloc_head = +size;

	return return_val;
}

void memory_test( void ) {
}