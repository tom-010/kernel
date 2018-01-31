;;kernel.asm

bits 32			;nasm directive - The first instruction bits
                ; 32 is not an x86 assembly instruction. It’s
                ; a directive to the NASM assembler that specifies
                ; it should generate code to run on a processor operating
                ; in 32 bit mode. It is not mandatorily required in our example,
                ; however is included here as it’s good practice to be explicit.

section .text   ; Here we put our code.
                ; The second line begins the text section (aka code section).
                ; This is where we put all our code.

        ;multiboot spec
        align 4
        dd 0x1BADB002            ;magic: containing the magic number 0x1BADB002, to identify the header.
        dd 0x00                  ;flags: We will not care about this field. We will simply set it to zero.
        dd - (0x1BADB002 + 0x00) ;checksum. m+f+c should be zero: the checksum field when added to the fields ‘magic’ and ‘flags’ must give zero.
       ;  \--The dd defines a double word of size 4 bytes.

global start    ;global is another NASM directive to set symbols from source code as global.
                ; By doing so, the linker knows where the symbol start is; which happens to
                ; be our entry point.

extern kmain    ;kmain is defined in the c file
                ; kmain is our function that will be defined in our kernel.c file. extern
                ; declares that the function is declared elsewhere

start:          ;Then, we have the start function, which calls the
                ; kmain function and halts the CPU using the hlt instruction.

  cli 			;block interrupts
                ; Interrupts can awake the CPU from an hlt instruction. So we disable interrupts beforehand using
                ; cli instruction. cli is short for clear-interrupts.
  mov esp, stack_space	;set stack pointer
                        ; Just before the kmain is called, the stack pointer (esp) is made to point to this
                        ; space using the mov instruction.
  call kmain
  hlt		 	;halt the CPU

section .bss
resb 8192		;8KB for stack
stack_space: