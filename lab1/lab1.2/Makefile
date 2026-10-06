# Target executable name
TARGET_EXEC := main

# Directories
BUILD_DIR := ./build
BIN_DIR := ./bin
SRC_DIR := ./src
INC_DIR := ./include

# Compiler and Flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -I$(INC_DIR)

# Debug vs Release configuration
# Usage: make BUILD=release
BUILD ?= debug
ifeq ($(BUILD),release)
    CXXFLAGS += -O3
else
    CXXFLAGS += -g -O0
endif

# Find all C++ source files in SRC_DIR
SRCS := $(shell find $(SRC_DIR) -name '*.cpp' 2>/dev/null)

# Generate object file paths inside BUILD_DIR
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Generate dependency file paths (.d files track header changes)
DEPS := $(OBJS:.o=.d)

# Default target
.PHONY: all clean run

all: $(BIN_DIR)/$(TARGET_EXEC)

# Link object files into final executable
$(BIN_DIR)/$(TARGET_EXEC): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)
	@echo "Build complete: $@"

# Compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# Include generated header dependencies
-include $(DEPS)

# Run the compiled program
run: all
	@$(BIN_DIR)/$(TARGET_EXEC)

# Clean build output
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
	@echo "Cleaned build artifacts."
