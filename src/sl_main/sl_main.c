/*
 * =====================================================================================
 *
 *       Filename:  sl_main.c
 *
 *    Description:  Defines the C-code kernel entry point, calls initialisation routines.
 *
 *        Version:  1.0
 *        Created:  2013年10月21日 16时58分38秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhangrui, v.mezhang@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include "multiboot.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"
#include "debug.h"
#include "mm.h"

// 定义 elf 相关信息数据
elf_t kernel_elf;

int sl_main(multiboot_t *mboot_ptr)
{
	// all our initialisation calls whill go in here.

	// 从 GRUB 提供的信息中获取到内核符号表和代码地址信息
	kernel_elf = elf_from_multiboot(mboot_ptr);
	// 初始化全局段描述符表
	init_gdt();
	// 初始化全局中断描述符表
	init_idt();

	monitor_clear();
	printk_color(rc_black, rc_red, "Hello ShenleOS!\n");
	printk_color(rc_black, rc_green, "This is a simple OS kernel, just for study.\nYou can copy it freely!\n\n");
	/***************************************************/
	asm volatile("int $0x3");
	asm volatile("int $0x4");
	// 初始化物理内存管理
	init_pmm(mboot_ptr);
	// 初始化虚拟内存管理
	init_vmm();
	// 初始化物理内存可用页
	init_page_pmm(mboot_ptr);
	// 初始化内核态堆管理
	init_heap();
	// 测试内核堆函数
	test_heap();
	
	// 初始化时钟中断
	//init_timer(20);
	
	// 解除对 INTR 中断的屏蔽
	asm volatile("sti");

	return 0;
}


