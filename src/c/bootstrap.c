#include "kernel.h"

int fputc( int c, FILE * stream ) {
	int ret_val = EOF;

	if( (int)stream == 0x0 ) {
		serial_write( c );
		ret_val = c;
	} else if ( (int)stream == 0x1 ) {
		terminal_putchar( c );
		ret_val = c;
	} else if ( (int)stream == 0x2 ) {
		// N/A
	} else {
		// TODO
	}

	return ret_val;
}

int fputs( const char * s, FILE * stream ) {
	int ret_val = EOF;

	for( unsigned int i = 0; i < strlen( s ); i++ ) {
		(int)stream == 2 ? serial_write( *(s + i) ) : terminal_putchar( *(s + i) );
	}

	return ret_val;
}

int putchar( char c ) {
	return fputc( c, stdout );
}

/* Basic putc wrapper for printf() to put a char on the screen
*/
void putc( void *p, char c ) {
	void *file_to_write_to = p;

//Kill the gcc warning of unused var since we're not supporting different streams right now
	file_to_write_to++;

	putchar( c );
}