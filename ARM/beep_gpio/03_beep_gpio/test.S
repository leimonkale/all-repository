.global _start
.global sys_delay
_start:  b	reset
	ldr  pc, _undef_handler
	ldr  pc, _swi_handler
	ldr  pc, _pre_handler
	ldr  pc, _data_handler
	ldr  pc, _reseerved_handler
	ldr  pc, _irq_handler
	ldr  pc, _fiq_handler
	
_undef_handler: .word  _undef_handler
_swi_handler:  .word  _swi_handler
_pre_handler: .word  _pre_handler
_data_handler: .word  _data_handler
_reseerved_handler: .word  _reseerved_handler
_irq_handler: .word  _irq_handler
_fiq_handler: .word  _fiq_handler


reset:
	/* set the cpu to SVC32 mode 禁止fiq irq*/
	mrs	r0, cpsr
	bic	r0, r0, #0x1f
	orr	r0, r0, #0xd3
	msr	cpsr,r0
	
	/* Set vector address in CP15 VBAR register */
	ldr	r0, =_start
	mcr	p15, 0, r0, c12, c0, 0	@Set VBAR
	
	
	@ 默认处于 SVC 模式  sp = 栈顶地址(地址大的一端)
	ldr  sp, svc_stack_top
	
	@ 修改模式 fiq  10001：FIQ   (cpsr后5位), 设置对应模式的栈地址
	mrs r0, cpsr
	bic r0, #0x1f
	orr r0, #0x11
	msr cpsr, r0
	@  ldr  sp, fiq_stack_top
	
	@ 修改模式  10000：User
	mrs r0, cpsr
	bic r0, #0x1f
	orr r0, #0x10
	msr cpsr, r0
	ldr  sp, user_stack_top
	
	bl  main

    loop1: 
        b loop1

sys_delay:
	stmfd sp!, {lr}
	loop:
        subs r0, r0, #1
		bge loop	
	ldmfd sp!, {pc}

	
svc_stack:  .space   128*4
svc_stack_top:  .word  svc_stack+128*4

user_stack:  .space   128*4
user_stack_top:  .word  user_stack+128*4

