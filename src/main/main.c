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
#include "printk.h"

int main(multiboot_t *mboot_ptr)
{
	// all our initialisation calls whill go in here.
	monitor_clear();
	monitor_write_color("Hello ShenleOS!\n", rc_black, rc_green);

	return 0xDEADBABA;
}


