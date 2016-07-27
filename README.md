# STM32F4XX Library
#### Very much a work in progress

## Setting up the Project

This library can be cloned directly into the top directory of your project (the `git submodule` works well for this).
Create another directory at the same level as the library called `bin`

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