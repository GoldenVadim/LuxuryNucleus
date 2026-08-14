add_library(graphics_vt OBJECT fb_client.cpp fonts.cpp)
target_link_libraries(lnucleus PRIVATE graphics_vt)

add_subdirectory(textcon)