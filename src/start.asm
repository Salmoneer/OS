[bits 32]
section .text.prologue
global _start
_start:
	call kernel_main

section .text

extern kernel_main
