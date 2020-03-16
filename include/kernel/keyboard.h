#if !defined(KEYBOARD_INCLUDED)
#define KEYBOARD_INCLUDED

char get_character( unsigned int scan_code );
char get_scancode( void );
void keyboard_interrupt_handler( void );

#endif