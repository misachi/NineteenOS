#ifndef SCREEN_H
#define SCREEN_H

# define VIDEO_ADDRESS 0xb8000
# define MAX_ROWS 25
# define MAX_COLS 80
# define WHITE_ON_BLACK 0x0f  // Write white on black background

# include <stdint.h>

// Use inline assembly to access device driver ports
// Read and write data to devices
unsigned char port_byte_in(unsigned short port)
{
    // A handy C wrapper function that reads a byte from the specified port
    // "=a" ( result ) means : put AL register in variable RESULT when finished
    // "d" ( port ) means : load EDX with port
    unsigned char result;
    __asm__("in %%dx , %%al " : "=a"(result) : "d"(port));
    return result;
}

void port_byte_out(unsigned short port, unsigned char data)
{
    __asm__("out %%al , %%dx " : : "a"(data), "d"(port));
}

unsigned short port_word_in(unsigned short port)
{
    unsigned short result;
    __asm__("in %%dx , %%ax " : "=a"(result) : "d"(port));
    return result;
}

void port_word_out(unsigned short port, unsigned short data)
{
    __asm__("out %%ax ,%%dx " : : "a"(data), "d"(port));
}

#endif