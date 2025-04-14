# Compiler and compiler flags
CC = gcc
CFLAGS = -Iinclude -Isrc

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Target executable name
TARGET = $(BIN_DIR)/philo

# Source files and object files
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# Default target
all: directories $(TARGET)

# Create necessary directories
directories:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)

# Compile the executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(OBJ_DIR)

fclean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

re: clean make

# Run the program
run: all
	$(TARGET) $(ARGS)

# Help information
help:
	@echo "Makefile for C projects"
	@echo "Usage:"
	@echo "  make          - Build the program"
	@echo "  make clean    - Remove build files"
	@echo "  make run      - Build and run the program"
	@echo "  make help     - Display this help information"

.PHONY: all clean run help directories