/*
 * =====================================================================================
 *
 *       Filename:  main.c
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
#include "monitor.h"
#include "timer.h"

int main(multiboot_t *mboot_ptr)
{
	// all our initialisation calls whill go in here.
	// 初始化全局段描述符表
	init_gdt();
	// 初始化全局中断描述符表
	init_idt();

	monitor_clear();
	printk_color(rc_black, rc_red, "Hello ShenleOS!\n");
	printk_color(rc_black, rc_green, "This is a simple OS kernel, just for study.\nYou can copy it freely!\n\n");
	/***************************************************/
	// 初始化时钟中断
	init_timer(20);
	
	// 解除对 INTR 中断的屏蔽
	asm volatile("sti");
	//asm volatile("int $0x3");
	//asm volatile("int $0x4");

	return 0;
}


