section .data
global __cbind_mov_size
__cbind_mov_size: db 2

section .text

global _cbind_functor
_cbind_functor:
;	push rbp
;	mov rbp, rsp

	mov R9, R8
	mov R8, RCX
	mov RCX, RDX
	mov RDX, RSI
	mov RSI, RDI
DEFAULT ABS
global __cbind_functor_state_offset
__cbind_functor_state_offset:
	mov RDI, 0xAABBCCDDEEFFEEDD

global __cbind_functor_jmp_offset
__cbind_functor_jmp_offset:
	mov rax, 0xAABBCCDDEEFFEEDD
	jmp rax
DEFAULT REL

global _cbind_boundary
_cbind_boundary:
	int 3
