# Compiler options
CXX = clang++
CXXFLAGS = -std=c++2a -Wall -Wextra -O3

# Directories
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

# File extensions
SRC_EXT = cpp
OBJ_EXT = o

# Source files
SRC_FILES := $(wildcard $(SRC_DIR)/*.$(SRC_EXT))
OBJ_FILES := $(patsubst $(SRC_DIR)/%.$(SRC_EXT), $(BUILD_DIR)/%.$(OBJ_EXT), $(SRC_FILES))

# Header files
HEADER_FILES := $(wildcard $(SRC_DIR)/*.h)

# Output binary name
TARGET = $(BIN_DIR)/main

# Default target
all: $(TARGET)

# Rule to build the binary
$(TARGET): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Rule to build object files
$(BUILD_DIR)/%.$(OBJ_EXT): $(SRC_DIR)/%.$(SRC_EXT) $(HEADER_FILES)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean the build directory
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

run: $(TARGET)
	@$(TARGET)

