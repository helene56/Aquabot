add_executable(${ProjectName}
    main.c
    blink.c
)

target_include_directories(${ProjectName} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(${ProjectName} 
    pico_stdlib 
    FreeRTOS-Kernel-Heap4
    pico_cyw43_arch_lwip_threadsafe_background
    hardware_adc
    LWIP_PORT 
    )

# Enable print functionality on usb & disable on uart
pico_enable_stdio_usb(${ProjectName}  1) 
pico_enable_stdio_uart(${ProjectName}  0)

pico_add_extra_outputs(${ProjectName})