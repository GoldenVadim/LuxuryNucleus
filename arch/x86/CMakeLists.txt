set(LINKER_SCRIPT "script.lds")
cmake_path(ABSOLUTE_PATH LINKER_SCRIPT)
target_link_options(lnucleus PRIVATE -T${LINKER_SCRIPT})
set_target_properties(lnucleus PROPERTIES LINK_DEPENDS "${LINKER_SCRIPT}")

add_library(arch_boot OBJECT boot.cpp)
add_library(arch_pmio OBJECT pmio.cpp)
target_link_libraries(lnucleus PRIVATE arch_boot arch_pmio)

add_subdirectory(multiboot2)