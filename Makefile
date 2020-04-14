# Borrowed from https://github.com/cfenollosa/os-tutorial/blob/master/13-kernel-barebones/Makefile

# Install cross-compiler on MacOs using brew
# brew tap nativeos/i386-elf-toolchain
# brew install i386-elf-binutils i386-elf-gcc

# $@ = target file
# $< = first dependency
# $^ = all dependencies

# First rule is the one executed when no parameters are fed to the Makefile
all: run

# Notice how dependencies are built as needed
kernel.bin: entry.o stdio.o string.o kernel.o
	i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

entry.o: boot/entry.asm
	nasm $< -f elf -o $@

stdio.o: kernel/stdio.c
	i386-elf-gcc -ffreestanding -c $< -o stdio.o

string.o: kernel/string.c
	i386-elf-gcc -ffreestanding -c $< -o string.o

kernel.o: kernel/main.c
	i386-elf-gcc -ffreestanding -c $< -o $@

boot_sect.bin: boot/loader.asm
	nasm $< -f bin -o $@

os.image: boot_sect.bin kernel.bin
	cat $^ > $@

run: os.image
	# qemu-system-i386 -f -drive format=raw,file=$<
	qemu-system-i386 -d guest_errors -fda $<

clean:
	-rm *.bin *.o *.dis *.image

