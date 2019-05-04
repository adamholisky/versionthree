#if !defined( MEMORY_INCLUDED )
#define MEMORY_INCLUDED

#define MMAP_GET_NUM 0
#define MMAP_GET_ADDR 1
#define PAGE_SIZE 4096

void memory_initalize( void );
void * k_malloc( uint32_t size );
void memory_test( void );

uint32_t mmap_read( uint32_t request, uint8_t mode );
uint32_t allocate_frame( void );

#endif