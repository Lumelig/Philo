# Compiler and compiler flags
CC = @gcc
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
	@echo "\033[1;32mProgram ready\033[0m ✅"

# Create necessary directories
directories:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

# Compile the executable
$(TARGET): $(OBJ)
	@echo "\033[1;33mLinking the program... \033[0m🌀"
	$(CC) $(CFLAGS) -o $@ $^

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@


# Clean build files
clean:
	@rm -rf $(OBJ_DIR)
	@echo "\033[1;32mObject directorie deleted\033[0m"

fclean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "\033[1;32mEverything is deleted\033[0m"

re: fclean all

# Run the program
run: all
	$(TARGET) $(ARGS)

# Help information
help:
	@echo "\033[1;32mMakefile for C Philo\033[0m"
	@echo "\033[1;34mUsage:\033[0m"
	@echo " \033[1;33mmake\033[0m               	- Build the program"
	@echo " \033[1;33mmake clean\033[0m         	- Remove object files"
	@echo " \033[1;33mmake fclean\033[0m        	- Remove all files"
	@echo " \033[1;33mmake run ARGS=\"...\"\033[0m 	- Build and run with arguments"
	@echo " \033[1;33mmake help\033[0m           	- Display this help information"


.PHONY: all clean run help directories