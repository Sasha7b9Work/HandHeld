# (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by

project (Device)

#set(CMAKE_UNITY_BUILD OFF)

message("------------------------------------------------------------------------ ${PROJECT_NAME}")

include_directories(
    ../common/VS_KEIL
    src/Hardware/HAL
    src
    ../common/GD32E23x_Firmware_Library_V1.2.0/Firmware/CMSIS/GD/GD32E23x/Include
    ../common/GD32E23x_Firmware_Library_V1.2.0/Firmware/GD32E23x_standard_peripheral/Include
)

add_definitions(-DGD32E230 -DTYPE_BOARD_799)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -MP -Wall")

add_compile_options(
    /wd4127
    /wd4820    # 'xxx': '4' bytes padding added after data member 'yyy'
)


file(GLOB SRC            src/*.*)
file(GLOB HARDWARE       src/Hardware/*.*)
file(GLOB HARDWARE_CMSIS src/Hardware/CMSIS/*.*)
file(GLOB HARDWARE_HAL   src/Hardware/HAL/*.*)

source_group(src            FILES ${SRC})
source_group(Hardware       FILES ${HARDWARE})
source_group(Hardware/CMSIS FILES ${HARDWARE_CMSIS})
source_group(Hardware/HAL   FILES ${HARDWARE_HAL})

add_library(${PROJECT_NAME}
    ${SRC}
    ${HARDWARE}
    ${HARDWARE_CMSIS}
    ${HARDWARE_HAL}
)
