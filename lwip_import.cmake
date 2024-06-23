add_library(LWIP_PORT INTERFACE)
target_include_directories(LWIP_PORT
    INTERFACE
       ${CMAKE_CURRENT_LIST_DIR}/lib/lwip/
    )