add_library(debug_logger OBJECT logger.cpp)
#add_library(debug_trace OBJECT trace.cpp)

target_link_libraries(lnucleus PRIVATE #debug_trace 
                                       debug_logger)