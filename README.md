# STM32F4XX Library
#### Very much a work in progress


## Installation
I will get to this...eventually

## Setting up the Project
The following lines must be added to the top of your Makefile:
```
# Change TOPDIR to directory that contains STM32Library submodule
TOPDIR=.

# Change OUTPUT to whatever final bin, hex, and elf files should be called
OUTPUT=main

MODULEDIR=$(TOPDIR)/STM32Library
include $(MODULEDIR)/Makefile_defines
include $(MODULEDIR)/Makefile_std_rules
```