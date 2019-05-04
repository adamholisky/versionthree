#include "kernel.h"
#include "stdio.h"

multiboot_info_t * multiboot_header;
uint32_t multiboot_start;
uint32_t multiboot_end;
uint32_t mb_magic;

void multiboot_initalize( uint32_t _mb_magic, multiboot_info_t * mbh ) {
	mb_magic = _mb_magic;
	multiboot_header = mbh;
    multiboot_start = (uint32_t)mbh;
    multiboot_end = (uint32_t)(sizeof( multiboot_info_t) + mbh );
}

multiboot_info_t * multiboot_get_header( void ) {
	return multiboot_header;
}

uint32_t multiboot_get_start( void ) {
    return multiboot_start;
}

uint32_t multiboot_get_end( void ) {
    return multiboot_end;
}

void multiboot_test( void ) {

	if( mb_magic != MULTIBOOT_BOOTLOADER_MAGIC ) {
		printf( "[Multiboot] mb_magic is wrong: 0x%08x\n", mb_magic );
		printf( "[Multiboot] mbinfo header: 0x%08X\n", multiboot_header );
		panic( );
	}

    printf( "[Multiboot] mb_boot_magic:    0x%08x\n", mb_magic );
    printf( "[Multiboot] mb_info:          0x%08x\n", multiboot_header );
    printf( "[Multiboot] mb_bl_name:       '%s'\n", (multiboot_header->boot_loader_name) + 0xC0000000 );
    printf( "[Multiboot] mb_flags:         0x%08x\n", multiboot_header->flags );
    printf( "[Multiboot] mem_lower:        0x%08x\n", multiboot_header->mem_lower );
    printf( "[Multiboot] mem_upper:        0x%08x\n", multiboot_header->mem_upper );

	if( ! CHECK_FLAG( multiboot_header->flags, 6 ) ) {
		printf( "Error: No Multiboot memory map was provided!\n" );
		panic( );
	}

	printf( "[Multiboot] Pass\n" );
}