/*
 * =====================================================================================
 *
 *       Filename:  types.h
 *
 *    Description:  一些类型的定义
 *
 *        Version:  1.0
 *        Created:  2013年10月28日 15时31分34秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhangrui, v.mezhang@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#ifndef INCLUDE_TYPES_H
#define INCLUDE_TYPES_H

#ifndef NULL
#define NULL 0
#endif

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

typedef unsigned int 	uint32_t;
typedef 	 int 	int32_t;
typedef unsigned short 	uint16_t;
typedef 	 short 	int16_t;
typedef unsigned char 	uint8_t;
typedef 	 char 	int8_t;

//进程标识符
typedef uint32_t pid_t;

#endif 	//INCLUDE TYPES_H
