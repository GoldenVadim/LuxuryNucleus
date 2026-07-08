ENTRY(init_boot)
SECTIONS {
    mmio_addr_alloc_kernel_start = 2M;
    . = mmio_addr_alloc_kernel_start;

    .headers :
    {
        KEEP(*(.headers.multiboot2))
    }

    .text :
    {
        mmio_addr_alloc_text_start = ABSOLUTE(.);
        *(.text)
        mmio_addr_alloc_text_end = ABSOLUTE(.);
    }

    .bss :
    {
        mmio_addr_alloc_bss_start = ABSOLUTE(.);
        *(.bss)
        mmio_addr_alloc_bss_end = ABSOLUTE(.);
    }

    .rodata :
    {
        mmio_addr_alloc_rodata_start = ABSOLUTE(.);
        *(.rodata)
        mmio_addr_alloc_rodata_end = ABSOLUTE(.);
    }

    .data :
    {
        mmio_addr_alloc_data_start = ABSOLUTE(.);
        *(.data)
        mmio_addr_alloc_data_end = ABSOLUTE(.);
    }

    .providers :
    {
        providers_graphics_start = ABSOLUTE(.);
        KEEP(*(.providers.graphics))
        providers_graphics_end = ABSOLUTE(.);
    }

    t1 = .;
    t2 = .;

    /DISCARD/ :
    {
        *(.eh_frame*)
    }

    mmio_addr_alloc_kernel_end = ABSOLUTE(.);
}