	.file	"auto.c"
	.section	.rodata
.LC0:
	.string	"%d\344\270\207\345\262\201\344\270\207\345\262\201\344\270\207\344\270\207\345\262\201!\n"
	.text
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	pushl	%ebx
	subl	$28, %esp
	movl	$5, %ebx
	movl	$0, %ebx
	jmp	.L2
.L3:
	movl	$.LC0, %eax
	movl	%ebx, 4(%esp)
	movl	%eax, (%esp)
	call	printf
	addl	$1, %ebx
.L2:
	cmpl	$4, %ebx
	jle	.L3
	addl	$28, %esp
	popl	%ebx
	movl	%ebp, %esp
	popl	%ebp
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 4.4.7 20120313 (Red Hat 4.4.7-3)"
	.section	.note.GNU-stack,"",@progbits
