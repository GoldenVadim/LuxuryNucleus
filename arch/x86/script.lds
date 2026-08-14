ENTRY(init_boot)

PHDRS
{
    ro PT_LOAD FLAGS(4);
    rx PT_LOAD FLAGS(5);
    rw PT_LOAD FLAGS(6);
}

SECTIONS
{
    mmio_addr_alloc_kernel_start = 1M;
    . = mmio_addr_alloc_kernel_start;

    .text :
    {
        KEEP(*(headers.*))

        mmio_addr_alloc_text_start = .;
        *(.text*)
        mmio_addr_alloc_text_end = .;
    } :rx

    .rodata :
    {
        mmio_addr_alloc_rodata_start = .;
        *(.rodata*)
        mmio_addr_alloc_rodata_end = .;
    } :ro

    providers :
    {
        providers_graphics_start = .;
        KEEP(*(providers.graphics))
        providers_graphics_end = .;
    } :ro

    .bss :
    {
        *(.bss*)
    } :rw

    .data :
    {
        mmio_addr_alloc_data_start = .;
        *(.data*)
        mmio_addr_alloc_data_end = .;
    } :rw

    mmio_addr_alloc_kernel_end = .;
}