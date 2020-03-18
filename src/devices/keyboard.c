#include "kernel.h"
#include <stdio.h>

unsigned char keyboard_map[128] = {
0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
'9', '0', '-', '=', '\b',	/* Backspace */
'\t',			/* Tab */
'q', 'w', 'e', 'r',	/* 19 */
't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
0,			/* 29   - Control */
'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
'\'', '`',   0,		/* Left shift */
'\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
'm', ',', '.', '/',   0,				/* Right shift */
	'*',
0,	/* Alt */
' ',	/* Space bar */
0,	/* Caps lock */
0,	/* 59 - F1 key ... > */
	0,   0,   0,   0,   0,   0,   0,   0,
0,	/* < ... F10 */
0,	/* 69 - Num lock*/
0,	/* Scroll Lock */
0,	/* Home key */
0,	/* Up Arrow */
0,	/* Page Up */
	'-',
0,	/* Left Arrow */
	0,
0,	/* Right Arrow */
	'+',
0,	/* 79 - End key*/
0,	/* Down Arrow */
0,	/* Page Down */
0,	/* Insert Key */
0,	/* Delete Key */
	0,   0,   0,
0,	/* F11 Key */
0,	/* F12 Key */
0,	/* All other keys are undefined */
};

unsigned char keyboard_map_shift[128] = {
0,  27, '!', '@', '#', '$', '%', '^', '&', '*', /* 9 */
'(', ')', '_', '+', '\b', /* Backspace */
'\t',     /* Tab */
'Q', 'W', 'E', 'R', /* 19 */
'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', /* Enter key */
0,      /* 29   - Control */
'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', /* 39 */
'"', '~',   0,    /* Left shift */
'|', 'Z', 'X', 'C', 'V', 'B', 'N',      /* 49 */
'M', '<', '>', '?',   0,        /* Right shift */
	'*',
0,  /* Alt */
' ',  /* Space bar */
0,  /* Caps lock */
0,  /* 59 - F1 key ... > */
	0,   0,   0,   0,   0,   0,   0,   0,
0,  /* < ... F10 */
0,  /* 69 - Num lock*/
0,  /* Scroll Lock */
0,  /* Home key */
0,  /* Up Arrow */
0,  /* Page Up */
	'-',
0,  /* Left Arrow */
	0,
0,  /* Right Arrow */
	'+',
0,  /* 79 - End key*/
0,  /* Down Arrow */
0,  /* Page Down */
0,  /* Insert Key */
0,  /* Delete Key */
	0,   0,   0,
0,  /* F11 Key */
0,  /* F12 Key */
0,  /* All other keys are undefined */
};

char current_scancode;
bool is_shift;

void keyboard_interrupt_handler( void ) {
	uint8_t status;
	char scancode;

	status = inportb( 0x64 );

	if( status & 0x01 ) {
		scancode = inportb( 0x60 );

		printf( " - %d - ", scancode );

		if( scancode == 42 || scancode == 54 ) {
			//printf( " +shift " );
			is_shift = true;
		} else if ( scancode == -86 || scancode == -74 ) {
			//printf( " -shift " );
			is_shift = false;
		}

		if( scancode > 0 ) {
			current_scancode = scancode;
		}
	}
}

char get_character( unsigned int scan_code ) {
	if( is_shift ) {
		return keyboard_map_shift[ scan_code ];
	}

	return keyboard_map[ scan_code ];}

char get_scancode( void ) {
	return 'b';
}