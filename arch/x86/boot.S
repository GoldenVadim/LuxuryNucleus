.intel_syntax noprefix

.section .bss
stack_bottom:
.align 16
.skip 16384
stack_top:


.code32
.section .text
.global init_boot
halt:
    cli
1:  hlt
    jmp 1b

init_boot:
    cmp eax, 0x36d76289
    jne halt

    mov esp, offset stack_top
    cmp esp, offset stack_top
    jne halt

    //call setup_paging
    call setup_tables
    jmp init_main