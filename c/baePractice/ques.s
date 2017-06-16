	.file	"ques.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"*p=%d\n"
.LC1:
	.string	"ci=%d\n"
	.text
	.p2align 4,,15
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$32, %esp
	movl	$10, 28(%esp)
	movl	$20, 28(%esp)
	movl	28(%esp), %eax
	movl	$.LC0, (%esp)
	movl	%eax, 4(%esp)
	call	printf
	movl	28(%esp), %eax
	movl	$.LC1, (%esp)
	movl	%eax, 4(%esp)
	call	printf
	leave
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 4.4.7 20120313 (Red Hat 4.4.7-3)"
	.section	.note.GNU-stack,"",@progbits
