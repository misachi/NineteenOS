#ifndef STRING_H
#define STRING_H

#include <stdint.h>

void memcopy(char *str1, const char *str2, const int8_t n);
int8_t strlen(const char *str);
void memsetw(uint16_t *block, char c, int16_t n);
void memsetb(char *block, char c, int8_t n);

#endif
