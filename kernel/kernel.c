// This is the entry routine to the kernel. 
void kernel_main() {
    char* video_memory = (char*) 0xb8000;
    *video_memory = 'X';
}
