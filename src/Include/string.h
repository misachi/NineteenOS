#ifndef STRING_H
#define STRING_H

#include "stdint.h"

void memcopy(char *str1, const char *str2, const uint16_t n);
uint8_t strlen(const char *str);
void memset(void *block, char c, uint16_t n);
char *strcpy(char *dest, const char *src);
#endif
