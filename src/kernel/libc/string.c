#include <string.h>
#include <stdint.h>

void memcopy(char *str1, const char *str2, const int8_t n)
{
    int8_t i;
    for (i = 0; i < n; i++)
        str1[i] = str2[i];
}

int8_t strlen(const char *str)
{
    int8_t len = 0;
    while (*str)
    {
        len++;
        str++;
    }
    return len;
}

void memsetb(char *block, char c, int8_t n)
{
    while(*block)
    {
        *block = c;
        block++;
    }
}

void memsetw(uint16_t *block, char c, int16_t n)
{
    while(*block)
    {
        *block = (uint16_t)c;
        block++;
    }
}

