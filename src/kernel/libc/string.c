#include <string.h>
#include <stdint.h>

void memcopy(char *str1, const char *str2, const uint16_t n)
{
    uint8_t i;
    for (i = 0; i < n; i++)
        str1[i] = str2[i];
}

uint8_t strlen(const char *str)
{
    uint8_t len = 0;
    while (*str)
    {
        len++;
        str++;
    }
    return len;
}

void memset8(char *block, char c, uint16_t n)
{
    while(n--)
    {
        *block++ = c;
    }
}

void memset16(uint16_t *block, char c, uint16_t n)
{
    while(n--)
    {
        *block++ = (uint16_t)c;
    }
}

void memset64(uint64_t *block, char c, uint16_t n)
{
    while(n--)
    {
        *block++ = (uint64_t)c;
    }
}

char *strcpy(char *dest, const char *src) {
	char *tmp = dest;

	while ((*dest++ = *src++) != '\0');
	return tmp;
}
