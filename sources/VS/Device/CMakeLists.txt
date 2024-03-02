# (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by

project (Device)

set(CMAKE_UNITY_BUILD OFF)

set(CMAKE_UNITY_BUILD_BATCH_SIZE 16)


include_directories(
    .
    Device
    ../../Device/src
    ../../Device/src/Hardware/CDC
    ../../Device/src/Hardware/HAL
    ../../ThirdParty/wxWidgets/include
    ../../generated/ThirdParty/lib/vc_dll/mswud
    ../../common/_VS_KEIL/CMSIS
    ../../common/_VS_LIBS/STM32F1
    ../../common/STM32Cube_F1/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc
    ../../common/STM32Cube_F1/Middlewares/ST/STM32_USB_Device_Library/Core/Inc
    ../../common/STM32Cube_F1/Drivers/CMSIS/Device/ST/STM32F1xx/Include
    ../../common/STM32Cube_F1/Drivers/STM32F1xx_HAL_Driver/Inc
)

link_directories(../../generated/ThirdParty/lib/vc_dll)

add_definitions(-DSTM32F103xB -DWXUSINGDLL -DGUI -DDEVICE)

if(WIN32)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -MP -Wall")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")

    add_compile_options(/wd4365)
    add_compile_options(/wd4514)
    add_compile_options(/wd4623)
    add_compile_options(/wd4625)
    add_compile_options(/wd4626)
    add_compile_options(/wd4774)
    add_compile_options(/wd4820)
    add_compile_options(/wd4996)
    add_compile_options(/wd5026)
    add_compile_options(/wd5027)
    add_compile_options(/wd5039)    # 'xxx': pointer or reference to potentially throwing function passed to extern C
                                    # function under -EHc.
    add_compile_options(/wd5045)
    add_compile_options(/wd5220)
    add_compile_options(/wd5267)
endif()

file(GLOB LIBS_USBD                 ../../common/_VS_LIBS/USBD/*.*)
file(GLOB SRC                       *.h *.cpp
                                    ../../Device/src/defines.h
                                    ../../Device/src/Device.*)
file(GLOB DISPLAY                   ../../Device/src/Display/*.*)
file(GLOB DISPLAY_FONT              ../../Device/src/Display/Font/*.*)
file(GLOB HARDWARE                  ../../Device/src/Hardware/*.*)
file(GLOB HARDWARE_HAL              ../../Device/src/Hardware/HAL/*.*
                                                     Hardware/HAL/*.*)
file(GLOB MODULES_CMT2210AW         ../../Device/src/Modules/CMT2210AW/*.*)
file(GLOB MODULES_PCF8563           ../../Device/src/Modules/PCF8563/*.*)
file(GLOB MODULES_ST7755            ../../Device/src/Modules/ST7755/*.*)
file(GLOB MENU                      ../../Device/src/Menu/*.*)
file(GLOB MENU_PAGES                ../../Device/src/Menu/Pages/*.*)
file(GLOB SETTINGS                  ../../Device/src/Settings/*.*)
file(GLOB UTILS                     ../../Device/src/Utils/*.*)

source_group(libs/USBD                  FILES ${LIBS_USBD})
source_group(src                        FILES ${SRC})
source_group(Display                    FILES ${DISPLAY})
source_group(Display/Font               FILES ${DISPLAY_FONT})
source_group(Hardware                   FILES ${HARDWARE})
source_group(Hardware/HAL               FILES ${HARDWARE_HAL})
source_group(Modules/CMT2210AW          FILES ${MODULES_CMT2210AW})
source_group(Modules/PCF8563            FILES ${MODULES_PCF8563})
source_group(Modules/ST7755             FILES ${MODULES_ST7755})
source_group(Menu                       FILES ${MENU})
source_group(Menu/Pages                 FILES ${MENU_PAGES})
source_group(Settings                   FILES ${SETTINGS})
source_group(Utils                      FILES ${UTILS})


set_source_files_properties(
    Application.cpp
    Frame.cpp
    main_win.cpp
    PROPERTIES SKIP_UNITY_BUILD_INCLUSION ON
)


set_source_files_properties(../../Device/src/Hardware/CDC/usbd_conf.c
                            PROPERTIES HEADER_FILE_ONLY TRUE)

add_executable(${PROJECT_NAME}
    ${LIBS_STM32F1}
    ${LIBS_STM32F1_INC}
    ${LIBS_USBD}
    ${SRC}
    ${DISPLAY}
    ${DISPLAY_FONT}
    ${HARDWARE}
    ${HARDWARE_HAL}
    ${MODULES_CMT2210AW}
    ${MODULES_PCF8563}
    ${MODULES_ST7755}
    ${MENU}
    ${MENU_PAGES}
    ${SETTINGS}
    ${UTILS}
)

target_link_libraries(${PROJECT_NAME} wxbase32ud wxmsw32ud_core Ws2_32)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND copy ..\\..\\ThirdParty\\lib\\vc_dll\\wxbase32ud_vc_custom.dll $(OutputPath) /Y)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND copy ..\\..\\ThirdParty\\lib\\vc_dll\\wxmsw32ud_core_vc_custom.dll $(OutputPath) /Y)
