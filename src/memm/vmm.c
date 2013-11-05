/*
 * =====================================================================================
 *
 *       Filename:  vmm.c
 *
 *    Description:  虚拟内存管理函数实现
 *
 *        Version:  1.0
 *        Created:  2013年11月05日 21时24分52秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhangrui, v.mezhang@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include "idt.h"
#include "string.h"
#include "mm.h"

// 页目录地址
uint32_t *page_directory = (uint32_t *)PAGE_DIR_VIRTUAL_ADDR;

// 页表地址
uint32_t *page_tables = (uint32_t *)PAGE_TABLE_VIRTUAL_ADDR;

// 当前页目录地址
page_directory_t *current_directory;

void init_vmm()
{
	int i;
	uint32_t cr0;

	// 注册页面错误中断处理函数
	register_interrupt_handler(14, &page_fault);

	// 创建一个页目录，此时未开启分页
	page_directory_t *pd = (page_directory_t *)pmm_alloc_page();

	// 清空整个页目录的数据为0
	bzero(pd, 0x1000);

	//页目录第一项用来映射最开始的4mb内存
	pd[0] = pmm_alloc_page() | PAGE_PRESENT | PAGE_WRITE;
	uint32_t *pt = (uint32_t *)(pd[0] & PAGE_MASK);

	// 左移12位
}
