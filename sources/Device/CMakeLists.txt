# (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by

project (Device)

set(CMAKE_UNITY_BUILD OFF)

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
    /wd4310
    /wd4514
    /wd4623
    /wd4626
    /wd4710
    /wd4820    # 'xxx': '4' bytes padding added after data member 'yyy'
    /wd4996
    /wd5027
    /wd5045
)


file(GLOB SRC               src/*.*)
file(GLOB DISPLAY           src/Display/*.*)
file(GLOB HARDWARE          src/Hardware/*.*)
file(GLOB HARDWARE_CMSIS    src/Hardware/CMSIS/*.*)
file(GLOB HARDWARE_HAL      src/Hardware/HAL/*.*)
file(GLOB KEYBOARD          src/Keyboard/*.*)
file(GLOB MENU              src/Menu/*.*)
file(GLOB MODULES_CMT2210AW src/Modules/CMT2210AW/*.*)
file(GLOB MODULES_PCF8563   src/Modules/PCF8563/*.*)
file(GLOB MODULES_ST7735    src/Modules/ST7735/*.*)

source_group(src               FILES ${SRC})
source_group(Display           FILES ${DISPLAY})
source_group(Hardware          FILES ${HARDWARE})
source_group(Hardware/CMSIS    FILES ${HARDWARE_CMSIS})
source_group(Hardware/HAL      FILES ${HARDWARE_HAL})
source_group(Keyboard          FILES ${KEYBOARD})
source_group(Menu              FILES ${MENU})
source_group(Modules/CMT2210AW FILES ${MODULES_CMT2210AW})
source_group(Modules/PCF8563   FILES ${MODULES_PCF8563})
source_group(Modules/ST7735    FILES ${MODULES_ST7735})

add_library(${PROJECT_NAME}
    ${SRC}
    ${DISPLAY}
    ${HARDWARE}
    ${HARDWARE_CMSIS}
    ${HARDWARE_HAL}
    ${MENU}
    ${KEYBOARD}
    ${MODULES_CMT2210AW}
    ${MODULES_PCF8563}
    ${MODULES_ST7735}
)
