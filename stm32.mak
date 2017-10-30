#This file is generated by VisualGDB.
#It contains GCC settings automatically derived from the board support package (BSP).
#DO NOT EDIT MANUALLY. THE FILE WILL BE OVERWRITTEN. 
#Use VisualGDB Project Properties dialog or modify Makefile or per-configuration .mak files instead.

#In order to build this project manually (outside VisualGDB), please provide TOOLCHAIN_ROOT, BSP_ROOT, EFP_BASE and TESTFW_BASE variables via Environment or Make command line
#Embedded toolchain
CC := $(TOOLCHAIN_ROOT)/bin/arm-eabi-gcc.exe
CXX := $(TOOLCHAIN_ROOT)/bin/arm-eabi-g++.exe
LD := $(CXX)
AR := $(TOOLCHAIN_ROOT)/bin/arm-eabi-ar.exe
OBJCOPY := $(TOOLCHAIN_ROOT)/bin/arm-eabi-objcopy.exe

#Additional flags
PREPROCESSOR_MACROS += ARM_MATH_CM3 STM32F103C8 USE_FREERTOS flash_layout STM32F103xB USE_HAL_LEGACY 
INCLUDE_DIRS += . $(BSP_ROOT)/FreeRTOS/Source/CMSIS_RTOS $(BSP_ROOT)/FreeRTOS/Source/Include $(BSP_ROOT)/FreeRTOS/Source/Portable/gcc/ARM_CM3 $(BSP_ROOT)/STM32F1xxxx/STM32F1xx_HAL_Driver/Inc $(BSP_ROOT)/STM32F1xxxx/STM32F1xx_HAL_Driver/Inc/Legacy $(BSP_ROOT)/STM32F1xxxx/CMSIS_HAL/Device/ST/STM32F1xx/Include $(BSP_ROOT)/STM32F1xxxx/CMSIS_HAL/Include
LIBRARY_DIRS += 
LIBRARY_NAMES += compactcpp
ADDITIONAL_LINKER_INPUTS += 
MACOS_FRAMEWORKS += 
LINUX_PACKAGES += 

CFLAGS += 
CXXFLAGS += 
ASFLAGS += 
LDFLAGS += --specs=nano.specs --specs=nosys.specs
COMMONFLAGS += -mcpu=cortex-m3 -mthumb
LINKER_SCRIPT := $(BSP_ROOT)/STM32F1xxxx/LinkerScripts/STM32F103C8_flash.lds

