# GNU ARM Embedded Toolchain
CC=arm-none-eabi-gcc
CXX=arm-none-eabi-g++
LD=arm-none-eabi-ld
AR=arm-none-eabi-ar
AS=arm-none-eabi-as
CP=arm-none-eabi-objcopy
OD=arm-none-eabi-objdump
NM=arm-none-eabi-nm
SIZE=arm-none-eabi-size
A2L=arm-none-eabi-addr2line

#############################

# Directory Structure
BINDIR=bin
INCDIR=Inc
SRCDIR=.
LIBDIR=Library
STARTUPDIR=Startup


# Linker Script
LDSCRIPT=Linkers/STM32F411XE.ld


#############################

# Find source files
ASOURCES=$(shell find -L $(STARTUPDIR) -name '*.s')
ASOURCESPP=$(shell find -L $(STARTUPDIR) -name '*.S')
CSOURCES=$(shell find -L $(SRCDIR) -name '*.c')
# CSOURCES+=$(shell find -L $(STARTUPDIR) -name '*.c')
CXXSOURCES=$(shell find -L $(SRCDIR) -name '*.cpp')
# CXXSOURCES+=$(shell find -L $(LIBDIR) -name '*.cpp')

# Find header files
INC+=$(INCDIR)
INC+=$(LIBDIR)
INC+=$(STARTUPDIR)
INCLUDES=$(INC:%=-I%)

# Find libraries
INCLUDES_LIBS=
LINK_LIBS=

# Create Object List
OBJECTS=$(ASOURCES:%.s=%.o)
OBJECTS+=$(ASOURCESPP:%.S=%.o)
OBJECTS+=$(CSOURCES:%.c=%.o)
OBJECTS+=$(CXXSOURCES:%.cpp=%.o)
# Define output files ELF & IHEX
BINELF=main.elf
BINHEX=main.hex
BINBIN=main.bin

#############################

# MCU Flags
MCFLAGS=-mcpu=cortex-m4 -mthumb -mlittle-endian \
-mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb-interwork
# COMPILE FLAGS
DEFS=-DSTM32F4XX
CFLAGS=-c $(MCFLAGS) $(DEFS) $(INCLUDES)
CXXFLAGS=-c $(MCFLAGS) $(DEFS) $(INCLUDES) -std=c++11
LDFLAGS =-T $(LDSCRIPT) $(MCFLAGS) --specs=nosys.specs $(INCLUDES_LIBS) $(LINK_LIBS) -g

#############################

# Build Rules
.PHONY: all release debug clean flash

all: release

release: $(BINDIR)/$(BINHEX) $(BINDIR)/$(BINBIN)

$(BINDIR)/$(BINHEX): $(BINDIR)/$(BINELF)
	$(CP) -O ihex $< $@
	@echo "Objcopy from ELF to  IHEX complete!\n"

$(BINDIR)/$(BINBIN): $(BINDIR)/$(BINELF)
	$(CP) -O binary $< $@
	@echo "Objcopy from ELF to BIN complete!\n"

$(BINDIR)/$(BINELF): $(OBJECTS)
	$(CXX) -g $(OBJECTS) $(LDFLAGS) -o $@
	@echo "Linking complete!\n"
	$(SIZE) $(BINDIR)/$(BINELF)

%.o: %.cpp
	$(CXX) -g $(CXXFLAGS) $< -o $@

%.o: %.c
	$(CC) -g $(CFLAGS) $< -o $@

%.o: %.s
	$(CC) -g $(CFLAGS) $< -o $@

%.o: %.S
	$(CC) -g $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(BINDIR)/$(BINELF) $(BINDIR)/$(BINHEX) $(BINDIR)/$(BINBIN) $(BINDIR)/output.map

flash: $(BINDIR)/$(BINBIN)
	~/Development/stlink/st-flash write $(BINDIR)/$(BINBIN) 0x8000000