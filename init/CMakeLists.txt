add_library(init_main OBJECT main.cpp)
target_link_libraries(lnucleus PRIVATE init_main)