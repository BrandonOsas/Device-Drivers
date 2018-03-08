# project name
APPNAME = main

# toolchain configuration
PREFIX = arm-none-eabi

# core type
CORE = cortex-m3

# Directories
APP_DIR					= .
STM32_DIR				= ../STM32F10xStdPeriphLib/v3_5_0
STM32_LIB_DIR_INCLUDE	= $(STM32_DIR)/inc
STM32_LIB_DIR_SRC		= $(STM32_DIR)/src
USBOTG_DIR				= ../STM32_USB_OTG_Driver
USBOTG_LIB_DIR_INCLUDE	= $(USBOTG_DIR)/inc
USBOTG_LIB_DIR_SRC		= $(USBOTG_DIR)/src
USBH_DIR				= ../STM32_USB_HOST_Library/Core
USBH_LIB_DIR_INCLUDE	= $(USBH_DIR)/inc
USBH_LIB_DIR_SRC		= $(USBH_DIR)/src
USBHMSC_DIR				= ../STM32_USB_HOST_Library/Class/MSC
USBHMSC_LIB_DIR_INCLUDE	= $(USBHMSC_DIR)/inc
USBHMSC_LIB_DIR_SRC		= $(USBHMSC_DIR)/src

# Files
ARM_CMSIS_OBJECTS		= core_cm3.o system_stm32f10x.o startup_stm32f10x_cl.o

STM32_OBJECTS			= stm32f10x_gpio.o stm32f10x_rcc.o misc.o stm32f10x_usart.o \
						  stm32f10x_pwr.o stm32f10x_dma.o stm32f10x_flash.o \
						  stm32f10x_spi.o stm32f10x_i2c.o stm32f10x_exti.o stm32f10x_tim.o

APP_OBJECTS				= $(APPNAME).o stm32fxxx_it.o usb_bsp.o usbh_usr.o ccsbcs.o ff.o \
						  fattime.o stm3210c_eval.o syscalls.o \
						  stm3210c_eval_ioe.o stm3210c_eval_lcd.o lcd_log.o

USBOTG_OBJECTS			= usb_hcd_int.o usb_core.o usb_hcd.o

USBH_OBJECTS			= usbh_stdreq.o usbh_core.o usbh_hcs.o usbh_ioreq.o

USBHMSC_OBJECTS			= usbh_msc_scsi.o usbh_msc_bot.o usbh_msc_core.o usbh_msc_fatfs.o

OBJS					= $(APP_OBJECTS) $(STM32_OBJECTS) $(ARM_CMSIS_OBJECTS) $(USBOTG_OBJECTS) $(USBH_OBJECTS) $(USBHMSC_OBJECTS)
HEADERS					= ffconf.h lcd_log_conf.h stm32f10x_conf.h

VPATH					= $(STM32_LIB_DIR_SRC);$(STM32_LIB_DIR_INCLUDE);$(USBOTG_LIB_DIR_SRC);$(USBOTG_LIB_DIR_INCLUDE);$(USBH_LIB_DIR_SRC);$(USBH_LIB_DIR_INCLUDE);$(USBHMSC_LIB_DIR_SRC);$(USBHMSC_LIB_DIR_INCLUDE);$(APP_DIR)

# Specify compiler to be used
CC = $(PREFIX)-gcc

# Specify compiler to be used
OBJCOPY = $(PREFIX)-objcopy

# core flags
CORE_FLAGS = -mcpu=$(CORE) -mtune=$(CORE) -mfix-cortex-m3-ldrd -mthumb

# gcc options
OPTIONS =	-DGCC_ARMCM3 \
			-DUSE_STM3210C_EVAL \
			-DUSE_USB_OTG_FS \
			-DPACK_STRUCT_END=__attribute\(\(packed\)\) \
			-DALIGN_STRUCT_END=__attribute\(\(aligned\(4\)\)\) \
			-O2 $(CORE_FLAGS) -Wall \
			-I$(APP_DIR) \
			-I$(STM32_LIB_DIR_INCLUDE) \
			-I$(USBOTG_LIB_DIR_INCLUDE) \
			-I$(USBH_LIB_DIR_INCLUDE) \
			-I$(USBHMSC_LIB_DIR_INCLUDE)

# set to 'yes' to optimize size by removing unused code and data during link phase
REMOVE_UNUSED = no

ifeq ($(REMOVE_UNUSED), yes)
  OPTIONS += -ffunction-sections -fdata-sections
endif

# Create output file
all: $(APPNAME).elf $(APPNAME).hex $(APPNAME).bin

$(APPNAME).bin : $(APPNAME).elf
	$(PREFIX)-objcopy $(APPNAME).elf -O binary $(APPNAME).bin

$(APPNAME).hex : $(APPNAME).elf
	$(PREFIX)-objcopy -O ihex -I elf32-littlearm $(APPNAME).elf $@

# Link object files
$(APPNAME).elf : $(OBJS) $(APPNAME).ld makefile
ifeq ($(REMOVE_UNUSED), yes)
	$(CC) -nostartfiles $(CORE_FLAGS) -T$(APP_DIR)/$(APPNAME).ld -g -Xlinker -gc-sections -Xlinker -Map -Xlinker $(APPNAME).map -o $@ $(OBJS)
else
	$(CC) -nostartfiles $(CORE_FLAGS) -T$(APP_DIR)/$(APPNAME).ld -Xlinker --no-gc-sections -Xlinker -Map -Xlinker $(APPNAME).map -o $@ $(OBJS)
endif

# Compil.e .c files
%.o:	$(APP_DIR)/%.c makefile $(HEADERS)
		$(CC) $(OPTIONS) -c $< -o $@

# Assemble .s files
%.o:	$(APP_DIR)/%.s makefile $(HEADERS)
		$(CC) $(OPTIONS) -c $< -o $@

clean:
	rm -f  *.elf *.map *.o *.bin *.hex
