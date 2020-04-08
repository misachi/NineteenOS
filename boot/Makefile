# Borrowed from https://github.com/cfenollosa/os-tutorial/blob/master/13-kernel-barebones/Makefile

# $@ = target file
# $< = first dependency
# $^ = all dependencies

# First rule is the one executed when no parameters are fed to the Makefile
all: run

# Notice how dependencies are built as needed
kernel.bin: kernel_entry.o kernel.o
	i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

kernel_entry.o: entry.asm
	nasm $< -f elf -o $@

kernel.o: kernel.c
	i386-elf-gcc -ffreestanding -c $< -o $@

bootsect.bin: loader.asm
	nasm $< -f bin -o $@

os-image.bin: bootsect.bin kernel.bin
	cat $^ > $@

run: os-image.bin
	# qemu-system-i386 -f -drive format=raw,file=$<
	qemu-system-i386 -fda $<

clean:
	-rm *.bin *.o *.dis

