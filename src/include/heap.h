/*
 * =====================================================================================
 *
 *       Filename:  heap.h
 *
 *    Description:  内核堆管理
 *
 *        Version:  1.0
 *        Created:  2013年11月18日 15时02分14秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhangrui, v.mezhang@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#ifndef INCLUDE_HEAP_H_
#define INCLUDE_HEAP_H_

#include "types.h"

// 堆开始地址
#define HEAP_START 0xD0000000

// 堆结束地址
#define HEAP_END 0xFF000000

// 内存快管理结构
typedef struct header {
	struct header *prev; 	// 前后内存块管理结构指针
	struct header *next;
	uint32_t allocated : 1; // 该内存块是否已经被申请
	uint32_t length : 31; 	// 当前内存块的长度
} header_t;

// 初始化堆
void init_heap();

// 内存申请
void *kmalloc(uint32_t len);

// 内存释放
void kfree(void *p);

// 测试内核堆申请释放
void test_heap();

#endif
