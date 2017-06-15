	.file	"passwd.c"
	.section	.rodata
.LC0:
	.string	"input pas:"
.LC1:
	.string	"%d"
	.text
.globl passw
	.type	passw, @function
passw:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	$.LC0, %eax
	movl	%eax, (%esp)
	call	printf
	movl	-12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$.LC1, (%esp)
	call	scan
	cmpl	$123, -12(%ebp)
	sete	%al
	movzbl	%al, %eax
	leave
	ret
	.size	passw, .-passw
	.section	.rodata
.LC2:
	.string	"login ok!"
.LC3:
	.string	"login failed!"
	.text
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$16, %esp
	call	passw
	cmpl	$1, %eax
	jne	.L4
	movl	$.LC2, %eax
	movl	%eax, (%esp)
	call	printf
	jmp	.L7
.L4:
	movl	$.LC3, (%esp)
	call	puts
.L7:
	leave
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 4.4.7 20120313 (Red Hat 4.4.7-3)"
	.section	.note.GNU-stack,"",@progbits
