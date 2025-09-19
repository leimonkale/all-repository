# 定义编译器
CC = arm-linux-gcc
LD = arm-linux-ld
OBJCOPY = arm-linux-objcopy

# 使用 wildcard 函数查找当前目录下所有 .c 文件
SRC_FILES := $(wildcard *.c)

# 使用 patsubst 函数将 .c 文件名替换为对应的 .o 文件名
OBJ_FILES := $(patsubst %.c, %.o, $(SRC_FILES))

# 添加汇编文件 (start.s)
ASM_FILE := test.S
ASM_OBJ  := test.o

# 将所有目标文件合并 (包括汇编生成的 .o)
ALL_OBJS := $(ASM_OBJ) $(OBJ_FILES)

# 输出文件名
ELF_FILE := test.elf
BIN_FILE := 1.bin

# 链接脚本
LDS_FILE := test.lds

# 默认目标
all: $(BIN_FILE)

# 规则：将汇编文件编译成目标文件
$(ASM_OBJ): $(ASM_FILE)
	$(CC) $< -o $@ -c

# 规则：将 .c 文件编译成 .o 文件 (使用模式规则，自动处理所有 .c)
%.o: %.c
	$(CC) $< -o $@ -c

# 规则：链接所有 .o 文件生成 .elf
$(ELF_FILE): $(ALL_OBJS)
	$(LD) $^ -o $@ -T$(LDS_FILE)

# 规则：将 .elf 转换为二进制 .bin 文件
$(BIN_FILE): $(ELF_FILE)
	$(OBJCOPY) -O binary $< $@

# 清理目标
clean:
	rm -f $(ALL_OBJS) $(ELF_FILE) $(BIN_FILE)

# 反汇编
asm:
	arm-linux-objdump -D $(ELF_FILE) > disassembly.txt

