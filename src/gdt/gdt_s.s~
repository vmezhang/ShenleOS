; 将GDT地址载入GDTR
; hurley 2013/7/26

[GLOBAL gdt_flush]

gdt_flush:
	mov eax, [esp+4] ; 参数eax寄存器
	lgdt [eax] 	 ; 加载到GDTR[修改原先grub设置]

	mov ax, 0x10 	 ; 加载我们的数据段描述符
	mov ds, ax 	 ; 更新所有可以更新的段寄存器
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:.flush  ; 远跳转，0x08是我们的代码段描述符
			 ;远跳转目的是清空流水线并串行化处理器
.flush:
	ret
