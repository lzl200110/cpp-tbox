STAGING_DIR := ../../../.staging

STAGING_INCLUDE := $(STAGING_DIR)/include
STAGING_LIB := $(STAGING_DIR)/lib

CCFLAGS := -I$(STAGING_INCLUDE) -I$(CONSTANT_INCLUDE)
CFLAGS := $(CCFLAGS) -std=c99
CXXFLAGS := $(CCFLAGS) -std=c++11
LDFLAGS := -L$(STAGING_LIB)
INSTALL_DIR := $(STAGING_DIR)
DESTDIR := $(STAGING_DIR)
prefix :=

TOOLCHAIN_PREFIX :=
AR := $(TOOLCHAIN_PREFIX)ar
AS := $(TOOLCHAIN_PREFIX)as
CXX := $(TOOLCHAIN_PREFIX)g++
CC := $(TOOLCHAIN_PREFIX)gcc
NM := $(TOOLCHAIN_PREFIX)nm
OBJCOPY := $(TOOLCHAIN_PREFIX)objcopy
OBJDUMP := $(TOOLCHAIN_PREFIX)objdump
STRINGS := $(TOOLCHAIN_PREFIX)strings
SSTRIP := $(TOOLCHAIN_PREFIX)sstrip
LSTRIP := $(TOOLCHAIN_PREFIX)lstrip
STRIP := $(TOOLCHAIN_PREFIX)strip

export    STAGING_INCLUDE STAGING_LIB INSTALL_DIR DESTDIR prefix
export    AR AS CC NM OBJCOPY OBJDUMP CXX STRIP SSTRIP STRINGS LSTRIP
export    CFLAGS CXXFLAGS LDFLAGS
