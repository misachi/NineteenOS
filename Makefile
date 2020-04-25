# Slightly changed from https://github.com/cfenollosa/os-tutorial/blob/master/13-kernel-barebones/Makefile

# Trying to compile the cross-compiler by yourself on MacOS is
# a total pain(at least for me).
# Install cross-compiler on MacOs using brew as below
# 	brew tap nativeos/i386-elf-toolchain
# 	brew install i386-elf-binutils i386-elf-gcc

# $@ = target file
# $< = first dependency
# $^ = all dependencies

# First rule is the one executed when no parameters are fed to the Makefile
INCLUDEDIRS := src/kernel/include
BIN := bin
CC := i386-elf-gcc
LD := i386-elf-ld
SOURCES = $(wildcard src/kernel/*.c src/kernel/libc/*.c)
OBJ = ${SOURCES:.c=.o}
CFLAGS := -m32 \
		-std=c99 \
		-Wall \
		-Wpedantic \
		-nostdlib -ffreestanding

all: run

kernel.bin: src/boot/entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

boot_sect.bin:
	nasm src/boot/loader.asm -f bin -o $@

bin/os_image: boot_sect.bin kernel.bin
	cat $^ > $@

run: bin/os_image
	# qemu-system-i386 -f -drive format=raw,file=$<
	qemu-system-i386 -d guest_errors -fda $<

%.o: %.c
	${CC} ${CFLAGS} -I ${INCLUDEDIRS} -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm src/boot/*.o *.bin ${OBJ}
