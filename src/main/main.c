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

int main(multiboot_t *mboot_ptr)
{
	// all our initialisation calls whill go in here.
	// 初始化全局段描述符表
	init_gdt();
	// 初始化全局中断描述符表
	init_idt();
	monitor_clear();
	monitor_write_color("Hello ShenleOS!\n", rc_black, rc_green);
	/***************************************************/
	asm volatile("int $0x3");
	asm volatile("int $0x4");

	return 0xDEADBABA;
}


