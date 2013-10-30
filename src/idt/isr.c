/*
 * =====================================================================================
 *
 *       Filename:  isr.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月30日 21时24分45秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhangrui, v.mezhang@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include "idt.h"
#include "monitor.h"

void isr_handler(pt_regs *regs)
{
	monitor_write("recieved interrupt: ");
	monitor_write_dec(regs->int_no, rc_black, rc_red);
	monitor_write("\n");
}
