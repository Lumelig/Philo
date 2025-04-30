# Compiler and compiler flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -Iinclude -Isrc

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Target executable name
TARGET = $(BIN_DIR)/philo

# Source files (manually listed)
SRC_FILES = main.c	dinner.c	getters_setters.c init.c monitor.c parsing.c safe_funktions.c \
				sync_utils.c  utils.c write_status.c 
SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# Default target
all: directories $(TARGET)
	@echo -e "\033[1;32mProgram ready\033[0m ✅"

# Create necessary directories
directories:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

# Compile the final binary
$(TARGET): $(OBJ)
	@echo -e "\033[1;33mLinking the program... \033[0m🌀"
	$(CC) $(CFLAGS) -o $@ $^

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	@rm -rf $(OBJ_DIR)
	@echo -e "\033[1;32mObject directory deleted\033[0m"

# Clean everything
fclean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo -e "\033[1;32mEverything is deleted\033[0m"

# Rebuild everything
re: fclean all

# Run the program
run: all
	$(TARGET) $(ARGS)

# Display help
help:
	@echo -e "\033[1;32mMakefile for C Philo\033[0m"
	@echo -e "\033[1;34mUsage:\033[0m"
	@echo -e " \033[1;33mmake\033[0m               	- Build the program"
	@echo -e " \033[1;33mmake clean\033[0m         	- Remove object files"
	@echo -e " \033[1;33mmake fclean\033[0m        	- Remove all files"
	@echo -e " \033[1;33mmake run ARGS=\"...\"\033[0m 	- Build and run with arguments"
	@echo -e " \033[1;33mmake help\033[0m           	- Display this help information"

.PHONY: all clean fclean re run help directories
