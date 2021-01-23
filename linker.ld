ENTRY(pm_mode)
SECTIONS 
{   
    . = 0x9000;
    .text : { *(.text) }
    .data : { *(.data) }
    .bss : { *(.bss) }
}
