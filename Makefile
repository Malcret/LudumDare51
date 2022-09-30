# Target name
NAME          := LudumDare51

# Default directories names
_SRCDIR       := src
_INCDIR       := inc
_LIBDIR       := lib
_BINDIR       := bin
_OBJDIR       := obj

# Directories
SRCDIR        := $(_SRCDIR)
INCDIR        := $(_INCDIR)
LIBDIR        := $(_LIBDIR)
BINDIR        := $(_BINDIR)
ifeq ($(BUILD), release)
CURRENTBUILD  := release
else
CURRENTBUILD  := debug
endif
BUILDDIR      := $(BINDIR)/$(CURRENTBUILD)
OBJDIR        := $(BUILDDIR)/$(_OBJDIR)

# Target
_TARGET       := $(NAME)
TARGET        := $(BUILDDIR)/$(_TARGET)

# Additional directories
SRCDIRS       := $(SRCDIR)\
                 $(SRCDIR)/Core
INCDIRS       := -I$(INCDIR) -I$(INCDIR)/external
LIBDIRS       := -L$(LIBDIR)
LIBFILES      := -lsfml-graphics -lsfml-window -lsfml-system
PCHFILE       := $(INCDIR)/PCH.hpp

# Detect OS and architecture
OSFLAGS :=
ifeq ($(OS),Windows_NT)
	OSNAME  := Win32
	OSFLAGS += -DWIN32
	ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
		ARCH    := AMD64
		OSFLAGS += -DAMD64
	else
		ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
			ARCH    := AMD64
			OSFLAGS += -DAMD64
		endif
		ifeq ($(PROCESSOR_ARCHITECTURE),x86)
			ARCH    := IA32
			OSFLAGS += -DIA32
		endif
	endif
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		OSNAME   = Linux
		OSFLAGS += -DLINUX
	endif
#	ifeq ($(UNAME_S),Darwin)
#		OSNAME   = OSX
#		OSFLAGS += -DOSX
#	endif
	UNAME_P := $(shell uname -p)
	ifeq ($(UNAME_P),x86_64)
		ARCH     = AMD64
		OSFLAGS += -DAMD64
	endif
	ifneq ($(filter %86,$(UNAME_P)),)
		ARCH     = IA32
		OSFLAGS += -DIA32
	endif
	ifneq ($(filter arm%,$(UNAME_P)),)
		ARCH     = ARM
		OSFLAGS += -DARM
	endif
endif

# Commands
CC    := gcc
CXX   := g++
AR    := ar
ifeq ($(OSNAME),Linux)
SH    :=
MKDIR := mkdir -p
RM    := rm -rf
endif
ifeq ($(OSNAME),Win32)
SH    := pwsh -noprofile -command
MKDIR := New-Item -ItemType Directory -Force
RM    := Remove-Item -Recurse -Force
endif

# Language versions
CCVERSION     := -std=c17
CXXVERSION    := -std=c++17

# C flags
CFLAGS        := $(CCVERSION) -Wall -Wextra $(INCDIRS) $(OSFLAGS)
ifeq ($(BUILD), release)
CFLAGS        += -DNDEBUG -DRELEASE -O2
else
CFLAGS        += -DDEBUG -g -Og
endif

# C++ flags
CXXFLAGS      := $(CXXVERSION) -Wall -Wextra $(INCDIRS) $(OSFLAGS)
ifeq ($(BUILD), release)
CXXFLAGS      += -DNDEBUG -DRELEASE -O2
else
CXXFLAGS      += -DDEBUG -g -Og
endif

# Linker flags
LDFLAGS       := $(LIBDIRS) $(LIBFILES)

# Source files
CCFILES          := $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.c))
CXXFILES         := $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.cpp))

# Object files
CCOBJFILES       := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.c.o, $(CCFILES))
CXXOBJFILES      := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.cpp.o, $(CXXFILES))
OBJFILES         := $(CCOBJFILES) $(CXXOBJFILES)

# C build rule
$(OBJDIR)/%.c.o: $(SRCDIR)/%.c
	$(SH) $(MKDIR) $(dir $@)
	$(SH) $(CC) $(CFLAGS) -c -o $@ $<

# C++ build rule
$(OBJDIR)/%.cpp.o: $(SRCDIR)/%.cpp
	$(SH) $(MKDIR) $(dir $@)
	$(SH) $(CXX) $(CXXFLAGS) -c -o $@ $<
	$(SH) $(CXX) $(CXXFLAGS) -c -o $@ $<

# Test target build rule
$(TARGET): $(OBJFILES)
	$(SH) $(CXX) -o $@ $^ $(LDFLAGS)

.PHONY: all build build_pch run clear cleanup mrproper

# Default make rule
all: build

# Build target
build: $(TARGET)
	@echo Build $(CURRENTBUILD) $(_TARGET) succesfully !

build_pch:
	$(SH) $(CXX) $(CXXFLAGS) $(PCHFILE)

# Run test
run:
	@echo Running $(_TARGET) $(CURRENTBUILD)...
	$(SH) ./$(TARGET)

# Clear target and object files for current build
clear:
	@echo Remove $(CURRENTBUILD) target and object files
ifneq ($(wildcard $(OBJDIR)/.),)
	$(SH) $(RM) $(OBJDIR)/*
endif
ifneq ($(wildcard $(TARGET)),)
	$(SH) $(RM) $(TARGET)
endif

# Clear target and object files for all build
cleanup:
	@echo Remove target and object files for all build
ifneq ($(wildcard $(BINDIR)/debug/$(_OBJDIR)/.),)
	$(SH) $(RM) $(BINDIR)/debug/$(_OBJDIR)/*
endif
ifneq ($(wildcard $(BINDIR)/debug/$(_TARGET)),)
	$(SH) $(RM) $(BINDIR)/debug/$(_TARGET)
endif
ifneq ($(wildcard $(BINDIR)/release/$(_OBJDIR)/.),)
	$(SH) $(RM) $(BINDIR)/release/$(_OBJDIR)/*
endif
ifneq ($(wildcard $(BINDIR)/release/$(_TARGET)),)
	$(SH) $(RM) $(BINDIR)/release/$(_TARGET)
endif

# Delete bin directory
mrproper:
	@echo Remove $(BINDIR) directory
	$(SH) $(RM) $(BINDIR)