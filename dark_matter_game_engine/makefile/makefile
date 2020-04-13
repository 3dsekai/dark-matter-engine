#*******************************************************************
#
# Dark Matter Game Engine Makefile
#
# Copyright (C) <2020> Christopher Tall
# License: GPLv3
#
#
# make file structure:
# target: dependencies
#	action
#
# manual:
# www.gnu.org/software/make/manual/make.html
#
# amazing article on make files for large projects:
# https://spin.atomicobject.com/2016/08/26/makefile-c-projects/
#
#*******************************************************************

#*******************************************************************
# variables
#*******************************************************************

# name of exe file
EXEC ?= a.out
# build directory to store all .o files
BUILD_DIR ?= ./build
# source directory
# SRC_DIR ?= ../dark_matter_game_engine/source
SRC_DIR ?= ../

#Automatic generation of source object files

# list of all source files
SRC := $(shell find $(SRC_DIR) -name *.cpp -or -name *.c)
# list of all object files
# (% = %.o -> all src files of name '%', change to %.o)
OBJ := $(SRC:%=$(BUILD_DIR)/%.o)
# list of all dependencies
DEP := $(OBJ:.o=.d)

#Automatic generation of include directory flags

# Directory for include files
# shell find: -type d -> get directory file type
INC_DIR := $(shell find $(SRC_DIR) -type d)
# include directory flags
INC_FLAGS := $(addprefix -I,$(INC_DIR))

# C/C++ flags.
# Automatically get all user header files in included in
# the source files, and create .d dependency files for the
# object files.
CPPFLAGS ?= $(INC_FLAGS) -MMD -MP

#opengl flags
LDFLAGS := -lglut -lGLU -lGL -lGLEW -lassimp
#*******************************************************************
# rules
#*******************************************************************
$(BUILD_DIR)/$(EXEC): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

# c source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR) # remove directories and their contents recursively

-include $(DEP)

# -p make parent directories as needed
MKDIR ?= mkdir -p
