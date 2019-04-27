.set ALIGN,    1<<0             /* align loaded modules on page boundaries */
.set MEMINFO,  1<<1             /* provide memory map */
.set FLAGS,    ALIGN | MEMINFO  /* this is the Multiboot 'flag' field */
.set MAGIC,    0x1BADB002       /* 'magic number' lets bootloader find the header */
.set CHECKSUM, -(MAGIC + FLAGS) /* checksum of above, to prove we are multiboot */
 
.section .multiboot
	.align 4
	.long MAGIC
	.long FLAGS
	.long CHECKSUM
 
.section .bootstrap_stack, "aw", @nobits
	.align 16
	stack_bottom:
	.skip 16384
	stack_top:

.section .bss, "aw", @nobits 
	.align 4096
	boot_page_directory:
	.skip 4096
	boot_page_table:
	.skip 4096
 

.section .text
.global _start
.type _start, @function
_start:
	movl $(boot_page_table - 0xC0000000), %edi		/* EDI gets the physical page table  address */
	movl $0, %esi									/* 0 == first address mapped */
	movl $1024, %ecx								/* Map our pages */

stage1:												/* Map the kernel (and the inital 1M) to the upper half */
	cmpl $(_kernel_end - 0xC0000000), %esi
	jge  stage2										/* Loop until we've mapped everything */

	movl %esi, %edx									/* Load physical address into EDX */
	orl  $0x003, %edx								/* Make the kernel's phsyical mem present and writeable */
	movl %edx, (%edi)								/* Move table entry to address pointed to in edi */
	addl $4096, %esi								/* Increment esi (physical address) by 4k */
	addl $4, %edi									/* Increment the table entry by 1 (1 entry == 32 bits == 4 bytes) */
	loop stage1

stage2:
	/* Setup physical 0 and 0xC0000000 to be present, writable so when we load CR3 we don't error out */
	movl $(boot_page_table - 0xC0000000 + 0x003), boot_page_directory - 0xC0000000
	movl $(boot_page_table - 0xC0000000 + 0x003), boot_page_directory - 0xC0000000 + 768 * 4

	movl $(boot_page_directory - 0xC0000000), %ecx	/* Correct for linker 0xC0000000 offset */
	movl %ecx, %cr3

	movl %cr0, %ecx
	orl  $0x80010000, %ecx							/* Enable w/4kb paging */
	movl %ecx, %cr0

	lea  stage3, %ecx
	jmp  *%ecx										/* BSG: "Jump" */

stage3:
	movl $0, boot_page_directory					/* Remove entry 0, since it's mapped now. Refresh cr3 */
	movl %cr3, %ecx
	movl %ecx, %cr3

	mov  $stack_top, %esp							/* Setup the stack */
	
	call kernel_main								/* Begin */

	hlt

.size _start, . - _start
