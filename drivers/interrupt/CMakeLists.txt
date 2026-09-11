add_library(driver_interrupt_nmi OBJECT nmi.cpp)
add_library(driver_interrupt_isr OBJECT isr.cpp)

target_compile_options(driver_interrupt_isr PRIVATE -mno-80387 -mno-sse -mno-mmx -mno-3dnow)
target_link_libraries(lnucleus PRIVATE driver_interrupt_nmi driver_interrupt_isr)