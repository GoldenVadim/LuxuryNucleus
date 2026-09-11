add_library(memory_alloc OBJECT alloc.cpp)
add_library(memory_ports OBJECT ports.cpp)

target_link_libraries(lnucleus PRIVATE memory_alloc memory_ports)