add_library(security_stack OBJECT stack_check.cpp)
add_library(security_cxa OBJECT cxa_guard.cpp)

target_link_libraries(lnucleus PRIVATE security_cxa security_stack)