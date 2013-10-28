/*
 * =====================================================================================
 *
 *       Filename:  gdt.h
 *
 *    Description:  GDT描述符定义
 *
 *        Version:  1.0
 *        Created:  2013年10月28日 15时18分41秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhangrui, v.mezhang@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#ifndef INCLUDE_GDT_H_
#define INCLUDE_DGT_H_

#include "types.h"

//全局描述符类型
typedef struct gdt_entry_t {
	uint16_t limit_low; 	//段界限 15~0
	uint16_t base_low; 	//段基地址 15~0
	uint8_t  base_middle; 	//段基地址 23~16
	uint8_t access; 	//段存在位、描述符特权级、描述符类型、描述符子类别
	uint8_t granularity; 	//其他标志、段界限 19~16
	uint8_t base_high; 	//段基地址 31~24
} __attribute__((packed)) gdt_entry_t;

//GDTR
typedef struct gdt_ptr_t {
	uint16_t limit; 	//全局描述符表限长
	uint32_t base; 		//全局描述符表32位基地址
} __attribute__((packed)) gdt_ptr_t;

//初始化全局描述符表
void init_gdt();

//GDT夹在到GDTR的函数[汇编实现]
extern void gdt_flush(uint32_t);

#endif 	//INCLUDE GDT H
