#ifndef PRINT_H
#define PRINT_H

#include <stdint.h>

void mov_cursor();
void print_char(char c);
void print(char *str);
void clear_screen(void);
void itoa(uint32_t i, uint32_t base, char* buf);
void itoa_s(uint32_t i, uint32_t base, char* buf);
int printf(const char *str, ...);
#endif