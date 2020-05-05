struc multiboot_info
    .flags               resd        1   ; required

    .mem_lower           resd        1   ; present if flags[0] is set
    .mem_upper           resd        1

    .boot_device         resd        1   ; present if flags[1] is set
    .cmdline             resd        1   ; present if flags[2] is set
                                        
    .mods_count          resd        1   ; present if flags[3] is set
    .mods_addr           resd        1

    .syms0		         resd	    1	; symbol table info. present if flags[4] or flags[5] is set
    .syms1		         resd	    1
    .syms2		         resd	    1
                                        
    .mmap_length         resd        1   ; present if flags[6] is set
    .mmap_addr           resd        1
                                        
    .drives_length       resd        1   ; present if flags[7] is set
    .drives_addr         resd        1

    .config_table        resd        1   ; present if flags[8] is set
    .boot_loader_name    resd        1   ; present if flags[9] is set
    .apm_table           resd        1   ; present if flags[10] is set

                                        
    .vbe_control_info    resd        1   ; present if flags[11] is set
    .vbe_mode_info       resd        1
    .vbe_mode            resw        1
    .vbe_interface_seg   resw        1
    .vbe_interface_off   resw        1
    .vbe_interface_len   resw        1
    
    .framebuffer_addr    resq        1   ; present if flags[12] is set
    .framebuffer_pitch   resd        1
    .framebuffer_width   resd        1
    .framebuffer_height  resd        1
    .framebuffer_bpp     resb        1
    .framebuffer_type    resb        1
    .color_info          resd        1
endstruc