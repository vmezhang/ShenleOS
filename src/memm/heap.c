/*
 * =====================================================================================
 *
 *       Filename:  heap.c
 *
 *    Description:  内核的简单堆管理
 *
 *        Version:  1.0
 *        Created:  2013年11月18日 15时13分23秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhangrui, v.mezhang@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include "mm.h"
#include "printk.h"

static void alloc_chunk(uint32_t start, uint32_t len);
static void free_chunk(header_t *chunk);
static void split_chunk(header_t *chunk, uint32_t len);
static void glue_chunk(header_t *chunk);

static uint32_t heap_max = HEAP_START;

// 内存块管理头指针
static header_t *heap_first = 0;

// 无需初始化
void init_heap()
{

}

void *kmalloc(uint32_t len)
{
	// 所有申请的内存长度加上管理头的长度
	// 因为在内存申请和释放的时候要通过该结构去管理
	len += sizeof(header_t);

	header_t *cur_header = heap_first;
	header_t *prev_header = 0;

	while (cur_header) {
		// 如果当前内存快没有被申请过而且长度大于待申请的块
		if (cur_header->allocated == 0 && cur_header->length >= len) {
			// 按照当前长度切割内存
			split_chunk(cur_header, len);
			cur_header->allocated = 1;
			// 返回的时候必须将指针挪到管理结构之后

			return (void *)((uint32_t)cur_header + sizeof(header_t));
		}
		// 逐次推移指针
		prev_header = cur_header;
		cur_header = cur_header->next;
	}

	uint32_t chunk_start;

	// 第一次执行该函数则初始化内存块起始位置
	// 之后根据当前指针加上申请的长度即可
	if (prev_header) {
		chunk_start = (uint32_t)prev_header + prev_header->length;
	} else {
		chunk_start = HEAP_START;
		heap_first = (header_t *)chunk_start;
	}

	// 检查是否需要申请页内存
	alloc_chunk(chunk_start, len);
	cur_header = (header_t *)chunk_start;
	cur_header->prev = prev_header;
	cur_header->next = 0;
	cur_header->allocated = 1;
	cur_header->length = len;

	if (prev_header) {
		prev_header->next = cur_header;
	}

	return (void *)(chunk_start + sizeof(header_t));
}

void kfree(void *p)
{
	// 指针回退到管理结构，并将已使用标记置0
	header_t *header = (header_t*)((uint32_t)p - sizeof(header_t));
	header->allocated = 0;

	// 粘合内存块
	glue_chunk(header);
}

void alloc_chunk(uint32_t start, uint32_t len)
{
	// 如果当前堆的位置已经达到界限则申请内存页
	// 必须循环申请内存页知道有足够的可用内存
	while (start + len > heap_max) {
		uint32_t page = pmm_alloc_page();
		map(heap_max, page, PAGE_PRESENT | PAGE_WRITE);
		heap_max += 0x1000;
	}
}

void free_chunk(header_t *chunk)
{
	if (chunk->prev == 0) {
		heap_first = 0;
	} else {
		chunk->prev->next = 0;
	}

	// 空闲的内存超过1页的话就释放掉
	while ((heap_max - 0x1000) >= (uint32_t)chunk) {
		heap_max -= 0x1000;
		uint32_t page;
		get_mapping(heap_max, &page);
		pmm_free_page(page);
		unmap(heap_max);
	}
}

void split_chunk(header_t *chunk, uint32_t len)
{
	// 切换内存块之前得保证之后的生育内存至少容纳一个内存管理块的大小
	if (chunk->length - len > sizeof(header_t)) {
		header_t *newchunk = (header_t *)((uint32_t )chunk + chunk->length);
		newchunk->prev = chunk;
		newchunk->next = chunk->next;
		newchunk->allocated = 0;
		newchunk->length = chunk->length - len;

		chunk->next = newchunk;
		chunk->length = len;
	}
}

void glue_chunk(header_t *chunk)
{
	// 如果该内存块后面有链接内存块且未被使用则拼合
	if (chunk->next && chunk->next->allocated == 0) {
		chunk->length = chunk->length + chunk->next->length;
		chunk->next->next->prev = chunk;
		chunk->next = chunk->next->next;
	}

	// 如果该内存块前面有链接内存块且未被使用则拼合
	if (chunk->prev && chunk->prev->allocated == 0) {
		chunk->prev->length = chunk->prev->length + chunk->length;
		chunk->prev->next = chunk->next;
		chunk->next->prev = chunk->prev;
		chunk = chunk->prev;
	}

	// 假如该内存后面没有链表内存块 直接释放掉
	if (chunk->next == 0) {
		free_chunk(chunk);
	}
}

void test_heap()
{
	printk_color(rc_black, rc_magenta, "Test kmalloc() && kfree() now ... \n\n");

	void *addr1 = kmalloc(50);
	printk("kmalloc 50 byte in 0x%X\n", addr1);
	void *addr2 = kmalloc(500);
	printk("kmalloc 500 byte in 0x%X\n", addr2);
	void *addr3 = kmalloc(5000);
	printk("kmalloc 5000 byte in 0x%X\n", addr3);
	void *addr4 = kmalloc(50000);
	printk("kmalloc 50000 byte in 0x%X\n\n", addr4);

	printk("free mem in 0x%X\n", addr1);
	kfree(addr1);
	printk("free mem in 0x%X\n", addr2);
	kfree(addr2);
	printk("free mem in 0x%X\n", addr3);
	kfree(addr3);
	printk("free mem in 0x%X\n\n", addr4);
	kfree(addr4);
}
