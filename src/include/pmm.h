/*
 * =====================================================================================
 *
 *       Filename:  pmm.h
 *
 *    Description:  页面内存管理
 *
 *        Version:  1.0
 *        Created:  2013年11月05日 20时49分27秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhangrui, v.mezhang@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#ifndef INCLUDE_PMM_H
#define INCLUDE_PMM_H

#include "multiboot.h"

// 物理内存管理的栈地址，放在寻址空间的较高位置
// 并通过这个地址管理所有的内存
#define PMM_STACK_ADDR 	0xFF000000

// 支持的最大物理内存(512MB)
#define PMM_MAX 0x20000000

// 初始化物理内存管理
void init_pmm(multiboot_t *mboot_ptr);

// 初始化分页内存管理
// 从空闲物理内存中取得内存页添加到内存页管理栈中
void init_page_pmm(multiboot_t *mboot_ptr);

// 返回一个内存页的物理地址
uint32_t pmm_alloc_page();

// 释放申请的内存
void pmm_free_page(uint32_t p);

// 是否开启内存分页
extern char mm_paging_active;


#endif
