#ifndef SCREEN_H
#define SCREEN_H

# define VIDEO_ADDRESS 0xb8000
# define MAX_ROWS 25
# define MAX_COLS 80
# define WHITE_ON_BLACK 0x0f  // Write white on black background

# include <stdint.h>

// Use inline assembly to access device driver ports
// Read and write data to devices
static inline uint8_t port_byte_in(uint16_t port)
{
    // A handy C wrapper function that reads a byte from the specified port
    // "=a" ( result ) means : put AL register in variable RESULT when finished
    // "d" ( port ) means : load EDX with port
    uint16_t result;
    __asm__("in %%dx , %%al " : "=a"(result) : "d"(port));
    return result;
}

static inline void port_byte_out(uint16_t port, uint8_t data)
{
    __asm__("out %%al , %%dx " : : "a"(data), "d"(port));
}

static inline uint16_t port_word_in(uint16_t port)
{
    uint16_t result;
    __asm__("in %%dx , %%ax " : "=a"(result) : "d"(port));
    return result;
}

static inline void port_word_out(uint16_t port, uint16_t data)
{
    __asm__("out %%ax ,%%dx " : : "a"(data), "d"(port));
}

#endif