add_library(memory_alloc OBJECT alloc.cpp)
add_library(memory_ports OBJECT ports.cpp)
#add_library(memory_paging OBJECT paging.cpp)
#add_library(memory_tables OBJECT tables.cpp)

target_link_libraries(lnucleus PRIVATE memory_alloc memory_ports  )