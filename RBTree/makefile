# Compiler and compiler flags
CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -DHEAP_SIZE_BYTES=4096

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INC_DIR = include

# Target executable
TARGET = $(BIN_DIR)/RBTree

# Source files and object files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Include paths
INCLUDES = -I$(INC_DIR)

# Rules
all: $(TARGET)

$(TARGET): $(OBJS)
    @mkdir -p $(BIN_DIR)
    $(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
    @mkdir -p $(OBJ_DIR)
    $(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<

clean:
    rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
