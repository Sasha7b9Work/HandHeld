# (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by

project (Device)

#set(CMAKE_UNITY_BUILD OFF)

message("------------------------------------------------------------------------ ${PROJECT_NAME}")

include_directories(
    ../common/_VS_KEIL/CMSIS
    ../common/_VS_KEIL/std_includes
    src/Hardware/HAL/GD
    ../common/GD32E23x_Firmware_Library_V1.2.0/Firmware/CMSIS/GD/GD32E23x/Include
    ../common/GD32E23x_Firmware_Library_V1.2.0/Firmware/GD32E23x_standard_peripheral/Include
    src
)

add_definitions(-DGD32E230 -DTYPE_BOARD_799)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -MP -Wall")

add_compile_options(
    /wd4201    # nonstandard extension used : nameless struct/union
    /wd4514    # 'function' : unreferenced inline function has been removed
    /wd4626    # assignment operator was implicitly defined as deleted
    /wd4710
    /wd4820    # 'xxx': '4' bytes padding added after data member 'yyy'
    /wd5027    # move assignment operator was implicitly defined as deleted
    /wd5045    # Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
    /wd5220    # a non-static data member with a volatile qualified type no longer implies
    /wd5264
)


file(GLOB SRC       src/*.*)

source_group(src    FILES ${SRC})

add_library(${PROJECT_NAME}
    ${SRC}
)
