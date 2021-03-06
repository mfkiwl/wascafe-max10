##########################################################################################################################
# File automatically-generated by tool: [projectgenerator] version: [3.10.0-B14] date: [Mon Sep 07 22:37:19 JST 2020] 
##########################################################################################################################

# ------------------------------------------------
# Generic Makefile (based on gcc)
#
# ChangeLog :
#	2017-02-10 - Several enhancements + project update mode
#   2015-07-22 - first version
# ------------------------------------------------

######################################
# target
######################################
TARGET = wasca


######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -O3


#######################################
# paths
#######################################
# source path
SOURCES_DIR =  \
Drivers/STM32F4xx_HAL_Driver \
Application \
Drivers/CMSIS \
Application/User \
Drivers

# firmware library path
PERIFLIB_PATH = 

# Build path
BUILD_DIR = build

######################################
# source
######################################
# C sources
C_SOURCES =  \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spi.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c \
Src/stm32f4xx_hal_msp.c \
Src/stm32f4xx_it.c \
Src/main.c \
Src/log.c \
Src/spi_max10.c \
Src/sdcard/fat_io_lib/fat_access.c \
Src/sdcard/fat_io_lib/fat_cache.c \
Src/sdcard/fat_io_lib/fat_filelib.c \
Src/sdcard/fat_io_lib/fat_format.c \
Src/sdcard/fat_io_lib/fat_global.c \
Src/sdcard/fat_io_lib/fat_internal.c \
Src/sdcard/fat_io_lib/fat_list.c \
Src/sdcard/fat_io_lib/fat_misc.c \
Src/sdcard/fat_io_lib/fat_string.c \
Src/sdcard/fat_io_lib/fat_table.c \
Src/sdcard/fat_io_lib/fat_write.c \
Src/sdcard/sdcard_fat.c \
Src/sdcard/sdcard_packet.c \
Src/sdcard/sdcard.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c \
Src/system_stm32f4xx.c


# ASM sources
ASM_SOURCES =  \
startup_stm32f446xx.s


######################################
# firmware library
######################################
PERIFLIB_SOURCES = 


#######################################
# binaries
#######################################
BINPATH = 
PREFIX = arm-none-eabi-
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
AR = $(PREFIX)ar
SZ = $(PREFIX)size
GDB = $(PREFIX)gdb
# Programming tools
OPENOCD = openocd
# Filetype flags
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m4

# fpu
FPU = -mfpu=fpv4-sp-d16

# float-abi
FLOAT-ABI = -mfloat-abi=hard

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \
-DUSE_HAL_DRIVER \
-DSTM32F446xx \
-DTARGET_STM32


# AS includes
AS_INCLUDES = 

# C includes
C_INCLUDES =  \
-IInc \
-IDrivers/STM32F4xx_HAL_Driver/Inc \
-IDrivers/STM32F4xx_HAL_Driver/Inc/Legacy \
-IDrivers/CMSIS/Device/ST/STM32F4xx/Include \
-IDrivers/CMSIS/Include


# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"


#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = STM32F446RETx_FLASH.ld

# libraries
LIBS = -lc -lm -lnosys 
LIBDIR = 
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

###############################################################################
# Upload commands
###############################################################################

OPENOCD_CFG = ../OpenOCD/stlink-v2-1.cfg
OPENOCD_TARGET_CFG = ../OpenOCD/stm32f4x.cfg
OPENOCD_ARGS  = -f $(OPENOCD_CFG)
OPENOCD_ARGS += -f $(OPENOCD_TARGET_CFG)
# Upload
OPENOCD_UPLOAD_CMDS  = -c init
OPENOCD_UPLOAD_CMDS += -c 'reset halt'
OPENOCD_UPLOAD_CMDS += -c 'sleep 10'
OPENOCD_UPLOAD_CMDS += -c 'flash write_image erase $(BUILD_DIR)/$(TARGET).hex'
OPENOCD_UPLOAD_CMDS += -c 'sleep 10'
OPENOCD_UPLOAD_CMDS += -c 'reset run'
OPENOCD_UPLOAD_CMDS += -c shutdown
# OpenOCD start debugging interface
OPENOCD_DEBUG_CMDS = -c init
OPENOCD_DEBUG_CMDS += -c 'halt'
OPENOCD_DEBUG_CMDS += -c 'sleep 10'
# GDB debugging commands
GDB_CMDS = -ex "target remote localhost:3333"
GDB_CMDS += -ex "file $(BUILD_DIR)/$(TARGET).elf"
GDB_CMDS += -ex "mon reset halt"
GDB_CMDS += -ex "tbreak main"
# Uncomment to allow application to run before user can attach to a GDB session
#GDB_CMDS += -ex "c"

###############################################################################
# Compilation targets
###############################################################################
# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@		

#######################################
# clean up
#######################################
clean:
	-rm -fR .dep $(BUILD_DIR)
  
# Upload program to target device
# N.B: Make sure you have permissions to access the STLink USB device
upload:
	$(OPENOCD) $(OPENOCD_ARGS) $(OPENOCD_UPLOAD_CMDS)

debug:
	$(OPENOCD) $(OPENOCD_ARGS) $(OPENOCD_DEBUG_CMDS)

run_gdb:
	$(GDB) $(GDB_ARGS) $(GDB_CMDS)

#######################################
# dependencies
#######################################
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)

# *** EOF ***
