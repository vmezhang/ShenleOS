/*
 * =====================================================================================
 *
 *       Filename:  elf.h
 *
 *    Description:  ELF格式的部分定义
 *
 *        Version:  1.0
 *        Created:  2013年11月06日 18时57分05秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhangrui, v.mezhang@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#ifndef INCLUDE_ELF_H_
#define INCLUDE_ELF_H_

#include "types.h"
#include "multiboot.h"

#define ELF32_ST_TYPE(i) ((i)&0xf)

// ELF格式区段头
typedef struct elf_section_header_t {
	uint32_t name;
	uint32_t type;
	uint32_t flags;
	uint32_t addr;
	uint32_t offset;
	uint32_t size;
	uint32_t link;
	uint32_t info;
	uint32_t addralign;
	uint32_t entsize;
} __attribute__((packed)) elf_section_header_t;

// ELF格式符号
typedef struct elf_symbol_t {
	uint32_t name;
	uint32_t value;
	uint32_t size;
	uint8_t info;
	uint8_t other;
	uint16_t shndx;
} __atrribute__((packed)) elf_symbol_t;

// ELF信息
typedef struct elf_t {
	elf_symbol_t 	*symtab;
	uint32_t 	symtabsz;
	const char 	*strtab;
	uint32_t 	strtabsz;
} elf_t;

// 从multiboot结构获取ELF信息
elf_t elf_from_multiboot(multiboot_t *mb);

// 察看ELF的符号信息
const char *elf_lookup_symbol(uint32_t addr, elf_t *elf);

#endif
