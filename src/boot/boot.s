;
; boot.s -- Kernel start location. Also define multiboot header.
;

MBOOT_PAGE_ALIGN equ 1<<0 	;load kernel and modues on a page boundary
MBOOT_MEM_INFO equ 1<<1 	;Provide your kernel with memory info
MBOOT_HEADER_MAGIC equ 0x1BADB002 	;Multiboot Magic value
; NOTE: We do not use MBOOT_AOUT_KLUDGE. It means that GRUB does not
; pass us a symbol table.
MBOOT_HEADER_FLAGS equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM 	   equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

[BITS 32] 		;ALl instructions should be 32-bit.

[GLOBAL mboot] 		;Make 'mboot' accessible from o;
[EXTERN code] 		;Start of the '.text' section.
[EXTERN bss] 		;Start of the .bss section.
[EXTERN end] 		;End of the last loadable section

mboot:
	dd MBOOT_HEADER_MAGIC 	;GRUB will search for this value on each
	
	dd MBOOT_HEADER_FLAGS 	;4-byte boundary in your kernel file
	dd MBOOT_CHECKSUM 	;To ensure that the above values are corret

	dd mboot 		;Location of this descriptor
	dd code 		;Start of kernel '.text'(code) section.
	dd bss 			;End of kernel '.data' section.
	dd end 			;End of kernel.
	dd start 		;Kernel entry point (initial EIP).

[GLOBAL start] 			;Kernel entry point.
[EXTERN main]  			;This is the entry point of our C code

start:
	push 	ebx 		;Load multiboot header location

				;Execute the kernel;
	cli 			;Disable interrupts.
	call main		;call out main() function.
	jmp $ 			;Enter an infinite loop, to stop the processor
				;executing whatever rubbish is in the memory
				;after our kernel!
