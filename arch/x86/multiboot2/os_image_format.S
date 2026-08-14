/* Multiboot2 OS image format
   Specification: https://www.gnu.org/software/grub/manual/multiboot2/ */
.intel_syntax noprefix

.macro TAG_HDR type, flags, size
    .short \type
    .short \flags
    .long \size
.endm

.section headers.multiboot2
.equ headers.multiboot2.length, headers.multiboot2.end - headers.multiboot2.start
headers.multiboot2.start:
    .long 0xE85250D6                                // magic
    .long 0                                         // arch
    .long headers.multiboot2.length                 // length
    .long -(0xE85250D6 + headers.multiboot2.length) // checksum
// tags start
    TAG_HDR 7 0 8
    TAG_HDR 0 0 8
// tags end
headers.multiboot2.end: