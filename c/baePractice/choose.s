	.file	"choose.c"
	.section	.rodata
	.align 4
.LC0:
	.string	"\346\254\242\350\277\216\345\212\240\345\205\245\345\260\232\350\247\202\357\274\214\346\214\221\346\210\230\351\253\230\350\226\252!"
.LC1:
	.string	"%d - CPP\n"
.LC2:
	.string	"%d - JAVA\n"
.LC3:
	.string	"%d - OCP\n"
.LC4:
	.string	"choose: "
.LC5:
	.string	"%d"
.LC6:
	.string	"\344\275\240\351\200\211\346\213\251\344\272\206\351\253\230\350\226\252!"
.LC7:
	.string	"\344\275\240\351\200\211\346\213\251\344\272\206\345\271\263\345\272\270!"
.LC8:
	.string	"\344\275\240\351\200\211\346\213\251\344\272\206\345\244\247\347\211\233!"
.LC9:
	.string	"\344\275\240\351\200\211\346\213\251\344\272\206ERROR"
	.text
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$32, %esp
	movl	$125, 28(%esp)
	movl	$.LC0, (%esp)
	call	puts
	movl	$.LC1, %eax
	movl	$0, 4(%esp)
	movl	%eax, (%esp)
	call	printf
	movl	$.LC2, %eax
	movl	$1, 4(%esp)
	movl	%eax, (%esp)
	call	printf
	movl	$.LC3, %eax
	movl	$2, 4(%esp)
	movl	%eax, (%esp)
	call	printf
	movl	$.LC4, %eax
	movl	%eax, (%esp)
	call	printf
	movl	$.LC5, %eax
	leal	28(%esp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	__isoc99_scanf
	movl	28(%esp), %eax
	cmpl	$1, %eax
	je	.L4
	cmpl	$2, %eax
	je	.L5
	testl	%eax, %eax
	jne	.L8
.L3:
	movl	$.LC6, (%esp)
	call	puts
	jmp	.L9
.L4:
	movl	$.LC7, (%esp)
	call	puts
	jmp	.L9
.L5:
	movl	$.LC8, (%esp)
	call	puts
	jmp	.L9
.L8:
	movl	$.LC9, (%esp)
	call	puts
.L9:
	leave
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 4.4.7 20120313 (Red Hat 4.4.7-3)"
	.section	.note.GNU-stack,"",@progbits
