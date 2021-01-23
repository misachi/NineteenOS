#include "./include/screen.h"
#include "./include/pic.h"

void i86_initialize_pic()
{
// ICW1
port_byte_out(MASTER_COMMAND, 0x11);
port_byte_out(SLAVE_COMMAND, 0x11);

// ICW2
port_byte_out(MASTER_DATA, 0x20);
port_byte_out(SLAVE_DATA, 0x28);

// ICW3
port_byte_out(MASTER_DATA, 0x04);
port_byte_out(SLAVE_DATA, 0x02);

// ICW4
port_byte_out(MASTER_DATA, 0x01);
port_byte_out(SLAVE_DATA, 0x01);

// Use processor local APIC and the IOAPICC. Disable PIC
port_byte_out(MASTER_DATA, 0xff);
port_byte_out(SLAVE_DATA, 0xff);
}