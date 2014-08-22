#!Makefile
#
# --------------------------------------------------------
#
#    ShenleOS 这个小内核的 Makefile
#    默认使用的C语言编译器是 GCC、汇编语言编译器是 nasm
#
# --------------------------------------------------------
#

# shell函数调用os中的命令
# patsubst 处理所有在 C_SOURCES 字列中的字（一列文件名），如果它的 结尾是 '.c'，就用 '.o' 把 '.c' 取代
C_SOURCES = $(shell find . -name "*.c")
C_OBJECTS = $(patsubst %.c, %.o, $(C_SOURCES))
S_SOURCES = $(shell find . -name "*.s")
S_OBJECTS = $(patsubst %.s, %.o, $(S_SOURCES))

CC = gcc
LD = ld
ASM = nasm

C_FLAGS = -c -Wall -m32 -ggdb -gstabs+ -nostdinc -fno-builtin -fno-stack-protector -I include
LD_FLAGS = -T link.ld -m elf_i386 -nostblib
ASM_FLAGS = -f elf -g

all: $(S_OBJECTS) $(C_OBJECTS) link update_image

# .c.o即后缀规则也可用%o:%c代替
# 使用@不显示以下执行的命令，使用echo之后的内容代替
# $<与$@为自动化变量
# $<为所有的目标文件集,$@为所有依赖目标文件集用于匹配目标中模式定义的集合
.c.o:
	@echo 编译代码文件 $< ...
	$(CC) $(C_FLAGS) $< -o $@

.s.o:
	@echo 编译汇编文件 $< ...
	$(ASM) $(ASM_FLAGS) $<

link:
	@echo 链接内核文件...
	$(LD) $(LD_FLAGS) $(S_OBJECTS) $(C_OBJECTS) -o kernel

# .PHONY之后是伪目标make时不执行
.PHONY:clean
clean:
	$(RM) $(S_OBJECTS) $(C_OBJECTS) kernel

.PHONY:update_image
update_image:
	sudo mount floppy.img /mnt/kernel
	sudo cp kernel /mnt/kernel/kernel
	sleep 1
	sudo umount /mnt/kernel

.PHONY:mount_image
mount_image:
	sudo mount floppy.img /mnt/kernel

.PHONY:umount_image
umount_image:
	sudo umount /mnt/kernel

.PHONY:qemu
qemu:
	qemu -fda floppy.img -boot a

.PHONY:bochs
bochs:
	bochs -f bochsrc.txt

.PHONY:debug
debug:
	gnome-terminal -e "bochs -f bochsrc.txt"
	sleep 1
	cgdb -x gdbinit
.PHONY:run
run:
	bochs -f bochsrc2.txt
