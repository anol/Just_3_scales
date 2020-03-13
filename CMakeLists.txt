cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CROSSCOMPILING 1)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_EXE_LINKER_FLAGS "--specs=nosys.specs" CACHE INTERNAL "")
set(GNU_TOOL_HOME "C:/Program Files (x86)/GNU Tools ARM Embedded/8 2019-q3-update")
set(CMAKE_C_FLAGS_INIT "-mtune=cortex-m3 -march=armv7-m -mthumb -Wall ")
set(CMAKE_CXX_FLAGS_INIT "-mtune=cortex-m3 -march=armv7-m -mthumb -Wall ")
set(CMAKE_LINKER ${GNU_TOOL_HOME}/bin/arm-none-eabi-gcc.exe)
set(CMAKE_ASM_COMPILER ${GNU_TOOL_HOME}/bin/arm-none-eabi-gcc.exe)

project(Just_3_scales VERSION 0.0)

add_executable(Just_3_scales.elf)

target_compile_options(Just_3_scales.elf PUBLIC
        -mtune=cortex-m3
        -march=armv7-m
        -mthumb
        -Wall)

target_compile_definitions(Just_3_scales.elf PUBLIC
        -Dgcc
        -DPART_TM4C123GH6PM
        -DTARGET_IS_TM4C123_RB2
        -DUART_BUFFERED)

target_link_options(Just_3_scales.elf PUBLIC
        -Wl,-Map=Just_3_scales.map
        -T ${CMAKE_CURRENT_SOURCE_DIR}/gcc.ld)

target_include_directories(Just_3_scales.elf PUBLIC
        src
        src/driverlib
        src/drivers
        src/main
        src/utils)

target_sources(Just_3_scales.elf PUBLIC
        src/driverlib/adc.c
        src/driverlib/adc.h
        src/driverlib/aes.c
        src/driverlib/aes.h
        src/driverlib/can.c
        src/driverlib/can.h
        src/driverlib/comp.c
        src/driverlib/comp.h
        src/driverlib/cpu.c
        src/driverlib/cpu.h
        src/driverlib/crc.c
        src/driverlib/crc.h
        src/driverlib/debug.h
        src/driverlib/des.c
        src/driverlib/des.h
        src/driverlib/eeprom.c
        src/driverlib/eeprom.h
        src/driverlib/emac.c
        src/driverlib/emac.h
        src/driverlib/epi.c
        src/driverlib/epi.h
        src/driverlib/flash.c
        src/driverlib/flash.h
        src/driverlib/fpu.c
        src/driverlib/fpu.h
        src/driverlib/gpio.c
        src/driverlib/gpio.h
        src/driverlib/hibernate.c
        src/driverlib/hibernate.h
        src/driverlib/i2c.c
        src/driverlib/i2c.h
        src/driverlib/interrupt.c
        src/driverlib/interrupt.h
        src/driverlib/lcd.c
        src/driverlib/lcd.h
        src/driverlib/mpu.c
        src/driverlib/mpu.h
        src/driverlib/onewire.c
        src/driverlib/onewire.h
        src/driverlib/pin_map.h
        src/driverlib/pwm.c
        src/driverlib/pwm.h
        src/driverlib/qei.c
        src/driverlib/qei.h
        src/driverlib/rom.h
        src/driverlib/rom_map.h
        src/driverlib/rtos_bindings.h
        src/driverlib/shamd5.c
        src/driverlib/shamd5.h
        src/driverlib/ssi.c
        src/driverlib/ssi.h
        src/driverlib/sw_crc.c
        src/driverlib/sw_crc.h
        src/driverlib/sysctl.c
        src/driverlib/sysctl.h
        src/driverlib/sysexc.c
        src/driverlib/sysexc.h
        src/driverlib/systick.c
        src/driverlib/systick.h
        src/driverlib/timer.c
        src/driverlib/timer.h
        src/driverlib/uart.c
        src/driverlib/uart.h
        src/driverlib/udma.c
        src/driverlib/udma.h
        src/driverlib/usb.c
        src/driverlib/usb.h
        src/driverlib/watchdog.c
        src/driverlib/watchdog.h
        src/drivers/adc_potmeter.cpp
        src/drivers/adc_potmeter.h
        src/drivers/alpha7segment.cpp
        src/drivers/alpha7segment.h
        src/drivers/pwm_stepper.cpp
        src/drivers/pwm_stepper.h
        src/drivers/qei_sensor.cpp
        src/drivers/qei_sensor.h
        src/drivers/ssi_display.cpp
        src/drivers/ssi_display.h
        src/drivers/ssi_drv8711.cpp
        src/drivers/ssi_drv8711.h
        src/drivers/ssi_peripheral.cpp
        src/drivers/ssi_peripheral.h
        src/main/commands.cpp
        src/main/commands.h
        src/main/main.cpp
        src/main/primary_activity.cpp
        src/main/primary_activity.h
        src/main/startup_gcc.c
#        src/main/tm4c123gh6pm_startup_ccs.c
        src/utils/cmdline.cpp
        src/utils/cmdline.h
        src/utils/uartstdio.cpp
        src/utils/uartstdio.h
        src/utils/ustdlib.cpp
        src/utils/ustdlib.h)
