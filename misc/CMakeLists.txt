add_library(misc_str_int OBJECT str_int.cpp)
target_link_libraries(lnucleus PRIVATE misc_str_int)

add_library(misc_delay OBJECT delay.cpp)
target_link_libraries(lnucleus PRIVATE misc_delay)