#include <screen.h>
#include <string.h>

uint8_t _CUR_X = 0;
uint8_t _CUR_Y = 0;

void mov_cursor()
{
    uint16_t temp = _CUR_X + _CUR_Y * MAX_COLS;
    port_byte_out(0x03D4, 0x0e);        // Activate high byte(Set Index reg)
    port_byte_out(0x03D5, temp >> 8);   // Send high byte
    port_byte_out(0x03D4, 0x0f);        // Activate low byte(Set Data reg)
    port_byte_out(0x03D5, temp);        // Send low byte
}

void print_char(char c)
{
    uint16_t attr = WHITE_ON_BLACK << 8;
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
        uint16_t *vid_memory = (uint16_t *)VIDEO_ADDRESS;
        uint16_t *temp = vid_memory + (_CUR_X + _CUR_Y * MAX_COLS); // Get position for character
        *temp = c | attr;   // Place the character in the position. Remembr attr is the colour byte and
                            // is in the upper byte. We combine with the character byte(lower byte)
                            // in order to display on screen

        _CUR_X++;           // Set X to the next position on screen
    }

    if (_CUR_X >= 80){
        _CUR_X = 0;
        _CUR_Y++;
    }
    mov_cursor();
}

void print(char *str){
    int8_t len = strlen(str);
    while(len)
    {
        print_char(*str);
        str++;
        len--;
    }
}