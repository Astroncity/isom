# Compiler selection
CC_LINUX = gcc
CC_WINDOWS = x86_64-w64-mingw32-gcc  # Change if using a different cross-compiler

# Compiler flags
CFLAGS_LINUX = -Wall -Wextra -Werror -ggdb -L lib/ -I include/ -lraylib -lm -lflecs
CFLAGS_WINDOWS = -Wall -Wextra -Werror -ggdb -L lib/ -I include/ -lraylibWin -lm -lflecsWin -lopengl32 -lgdi32 -lwinmm -lws2_32

DEPFLAGS = -MMD -MP

# Directories
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

# Output executable names
OUTPUT_NAME = output
OUTPUT_LINUX = $(OUTPUT_NAME)_linux
OUTPUT_WINDOWS = $(OUTPUT_NAME)_windows.exe

# Source files and object files
SRC_FILES = $(shell find $(SRC_DIR) -name '*.c')
OBJ_FILES = $(patsubst $(SRC_DIR)/%, $(BUILD_DIR)/%, $(SRC_FILES:.c=.o))
DEP_FILES = $(OBJ_FILES:.o=.d)

# Colors for output
RED = \033[0;31m
GREEN = \033[0;32m
BLUE = \033[0;34m
YELLOW = \033[0;33m
RESET = \033[0m
ACTION = $(YELLOW) [ACTION] $(RESET)
INFO = $(BLUE) [INFO] $(RESET)

# Default target (Linux build)
all: linux

# Linux build
linux: CC = $(CC_LINUX)
linux: CFLAGS = $(CFLAGS_LINUX)
linux: directories $(BIN_DIR)/$(OUTPUT_LINUX)
	@printf "$(INFO) Linux build complete. Executable '$(OUTPUT_LINUX)' created in $(BIN_DIR).\n"

$(BIN_DIR)/$(OUTPUT_LINUX): $(OBJ_FILES)
	@printf "$(ACTION) Linking for Linux...\n"
	@$(CC) $^ -o $@ $(CFLAGS)

# Windows build
windows: CC = $(CC_WINDOWS)
windows: CFLAGS = $(CFLAGS_WINDOWS)
windows: directories $(BIN_DIR)/$(OUTPUT_WINDOWS)
	@printf "$(INFO) Windows build complete. Executable '$(OUTPUT_WINDOWS)' created in $(BIN_DIR).\n"

$(BIN_DIR)/$(OUTPUT_WINDOWS): $(OBJ_FILES)
	@printf "$(ACTION) Linking for Windows...\n"
	@$(CC) $^ -o $@ $(CFLAGS)

# Compile each source file to an object file
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@printf "$(ACTION) Compiling $< to $@...\n"
	@$(CC) -c $< -o $@ $(CFLAGS) $(DEPFLAGS)

# Include dependency files
-include $(DEP_FILES)

# Create directories if they don't exist
directories:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)

# Clean the build and bin directories
clean:
	@printf "$(ACTION) Cleaning build and bin directories...\n"
	@rm -rf $(BUILD_DIR)/*
	@rm -rf $(BIN_DIR)/*

# Phony targets
.PHONY: all linux windows directories clean
