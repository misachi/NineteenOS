# Trying to compile the cross-compiler by yourself on MacOS is
# a total pain(at least for me).
# Install cross-compiler on MacOs using brew as below
# 	brew tap nativeos/i386-elf-toolchain
# 	brew install i386-elf-binutils i386-elf-gcc

# $@ = target file
# $< = first dependency
# $^ = all dependencies

# First rule is the one executed when no parameters are fed to the Makefile
KERNEL_INCLUDE := src/kernel/include
LIBC_INCLUDE := src/Include
BIN := bin
CC := i386-elf-gcc
LD := i386-elf-ld
SOURCES = $(wildcard src/kernel/*.c src/libc/*.c src/*.c)
OBJ = ${SOURCES:.c=.o}
CFLAGS := -m32 \
		-std=c11 \
		-Wall \
		-Woverflow \
		-Wpedantic \
		-nostdlib -ffreestanding

all: run

kernel.bin: src/boot/Stage2/loader.o src/boot/Stage2/entry.o ${OBJ}
	${LD} -o $@ -T linker.ld $^ --oformat binary

boot_sect.bin: kernel.bin
	nasm src/boot/Stage1/loader.asm -f bin -o $@

bin/os_image: boot_sect.bin kernel.bin
	cat $^ > $@

run: bin/os_image
	qemu-system-i386  -m 2G -d guest_errors -fda $<

%.o: %.c
	${CC} ${CFLAGS} -I${INCLUDEDIRS} -I${LIBC_INCLUDE} -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm src/boot/Stage2/*.o *.bin ${OBJ}
