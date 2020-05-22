#include <screen.h>
#include <string.h>
#include <va_list.h>
#include <stdarg.h>

uint8_t _CUR_X = 0;
uint8_t _CUR_Y = 0;
uint16_t *vid_memory = (uint16_t *)VIDEO_ADDRESS;

void mov_cursor()
{
    uint16_t temp = _CUR_X + _CUR_Y * MAX_COLS;
    port_byte_out(0x03D4, 0x0e);      // Activate high byte(Set Index reg)
    port_byte_out(0x03D5, temp >> 8); // Send high byte
    port_byte_out(0x03D4, 0x0f);      // Activate low byte(Set Data reg)
    port_byte_out(0x03D5, temp);      // Send low byte
}

void print_char(char c)
{
    uint16_t attr = (CYAN << 4 | RED) << 8;  // Red on Cyan background
    if (c == '\n')
    {
        _CUR_Y++;
        _CUR_X = 0;
    }
    else if (c == '\r')
    {
        _CUR_X = 0;
    }
    else if (c == 0x09) // Tab
    {
        _CUR_X = (_CUR_X + 8) & ~(8 - 1);
    }
    else if (c == 0x08) // Backspace
    {
        _CUR_X--;
    }
    else if (c >= ' ')
    {
        uint16_t *temp = vid_memory + (_CUR_X + _CUR_Y * MAX_COLS); // Get position for character
        *temp = c | attr;                                           // Place the character in the position. Remembr attr is the colour byte and
                                                                    // is in the upper byte. We combine with the character byte(lower byte)
                                                                    // in order to display on screen

        _CUR_X++; // Set X to the next position on screen
    }

    if (_CUR_X >= 80)
    {
        _CUR_X = 0;
        _CUR_Y++;
    }
    mov_cursor();
}

void print(char *str)
{
    uint8_t len = strlen(str);
    while (len)
    {
        print_char(*str);
        str++;
        len--;
    }
}

void clear_screen(void)
{
    uint16_t len = 2 * MAX_COLS * MAX_ROWS;
    uint16_t attributeByte = (CYAN << 4) << 8; // Cyan background
    uint16_t blank = 0x20 | (attributeByte);

    while (len--)
    {
        vid_memory[len] = blank;
    }
}

char tbuf[32];
char bchars[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

void itoa(uint32_t i, uint32_t base, char *buf)
{
    int32_t pos = 0;
    int32_t opos = 0;
    int32_t top = 0;

    if (i == 0 || base > 16)
    {
        buf[0] = '0';
        buf[1] = '\0';
        return;
    }

    while (i != 0)
    {
        tbuf[pos] = bchars[i % base];
        pos++;
        i /= base;
    }
    top = pos--;
    for (opos = 0; opos < top; pos--, opos++)
    {
        buf[opos] = tbuf[pos];
    }
    buf[opos] = 0;
}

void itoa_s(int32_t i, uint32_t base, char *buf)
{
    if (base > 16)
        return;
    if (i < 0)
    {
        *buf++ = '-';
        i *= -1;
    }
    itoa(i, base, buf);
}

int printf(const char *str, ...)
{

    if (!str)
        return 0;

    va_list args;
    va_start(args, str);
    uint64_t i;

    for (i = 0; i < strlen(str); i++)
    {
        switch (str[i])
        {
        case '%':
            switch (str[i + 1])
            {
            case 'c':
            {
                char c = va_arg(args, char);
                print_char(c);
                i++;
                break;
            }
            case 's':
            {
                char *c = va_arg(args, char*);
                char str[64];
                strcpy(str, (const char *)c);
                print(str);
                i++;
                break;
            }
            case 'u':
            {
                uint32_t c = va_arg(args, int);
                char str[32] = {0};
                itoa(c, 10, str);
                print(str);
                i++;
                break;
            }

            case 'd':
            case 'i':
            {
                int c = va_arg(args, int);
                char str[32] = {0};
                itoa_s(c, 10, str);
                print(str);
                i++;
                break;
            }

            case 'X':
            case 'x':
            {
                int c = va_arg(args, int);
                char str[32] = {0};
                itoa_s(c, 16, str);
                print(str);
                i++;
                break;
            }

            default:
                va_end(args);
                return 1;
            }

            break;

        default:
            print_char(str[i]);
            break;
        }
    }

    va_end(args);
    return i;
}
