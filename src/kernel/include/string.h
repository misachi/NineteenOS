#ifndef STRING_H
#define STRING_H

#include <stdint.h>

void memcopy(char *str1, const char *str2, const uint16_t n);
uint8_t strlen(const char *str);
void memset16(uint16_t *block, char c, uint16_t n);
void memset8(char *block, char c, uint16_t n);
void memset64(uint64_t *block, char c, uint16_t n);

#endif
