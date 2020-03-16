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
	multiboot_memory_map_t *mmap;

	if( mb_magic != MULTIBOOT_BOOTLOADER_MAGIC ) {
		debug_f( "[Multiboot] mb_magic is wrong: 0x%08x\n", mb_magic );
		debug_f( "[Multiboot] mbinfo header: 0x%08X\n", multiboot_header );
		panic( );
	}

    debug_f( "[Multiboot] mb_boot_magic:    0x%08x\n", mb_magic );
    debug_f( "[Multiboot] mb_info:          0x%08x\n", multiboot_header );
    debug_f( "[Multiboot] mb_bl_name:       '%s'\n", (multiboot_header->boot_loader_name) + 0xC0000000 );
    debug_f( "[Multiboot] mb_flags:         0x%08x\n", multiboot_header->flags );
	debug_f( "[Multiboot] mem_upper:        0x%08x\n", multiboot_header->mem_upper );
	debug_f( "[Multiboot] mem_lower:        0x%08x\n", multiboot_header->mem_lower );
	debug_f( "[Multiboot] mmap_length       %d\n", multiboot_header->mmap_length );
	debug_f( "[Multiboot] mmap_addr         0x%08x\n", multiboot_header->mmap_addr );

	debug_f( "---Begin memory map---\n" );
	for (mmap = (multiboot_memory_map_t *) (multiboot_header->mmap_addr + kernel_memory_base);
                (unsigned long) mmap < (multiboot_header->mmap_addr + kernel_memory_base) + multiboot_header->mmap_length;
                mmap = (multiboot_memory_map_t *) ((unsigned long) mmap
                                         + mmap->size + sizeof (mmap->size))) 
	{
             debug_f (" size = 0x%x, base_addr = 0x%x:%08x,"
                     " length = 0x%x:%08x, type = 0x%x\n",
                     (unsigned) mmap->size,
                     (unsigned) (mmap->addr >> 32),
                     (unsigned) (mmap->addr & 0xffffffff),
                     (unsigned) (mmap->len >> 32),
                     (unsigned) (mmap->len & 0xffffffff),
                     (unsigned) mmap->type);
	}

	debug_f( "---End memory map---\n" );

	debug_f( "[Multiboot] Pass\n" );
}