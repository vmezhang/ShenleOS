;将IDT地址载入IDTR

[GLOBAL idt_flush]
idt_flush:
	mov eax, [esp+4] 	; 参数存入eax寄存器
	lidt [eax] 		; 加载到IDTR
	ret
