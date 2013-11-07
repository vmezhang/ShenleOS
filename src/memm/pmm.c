/*
 * =====================================================================================
 *
 *       Filename:  pmm.c
 *
 *    Description:  页内存管理
 *
 *        Version:  1.0
 *        Created:  2013年11月07日 21时28分31秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhangrui, v.mezhang@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include "common.h"
#include "mm.h"

// 当前申请到的位置
uint32_t pmm_stack_loc = PMM_STACK_ADDR;

// 内存申请的界面位置
uint32_t pmm_stack_max = PMM_STACK_ADDR;

// 没有开启分页机制时的内存管理方案采用的管理指针
uint32_t pmm_location;

// 是否开启内存分页
char mm_paging_active = 0;

void init_pmm(multiboot *mboot_ptr)
{
	
}
