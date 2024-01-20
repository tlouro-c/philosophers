# Sample Makefile
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(INCLUDE_DIR) -I.include -lpthread #-fsanitize=thread -static-libasan -g
NAME = philo

INCLUDE_DIR = ./include
SRC_DIR = ./src
OBJ_DIR = ./obj

SRC_FILES =  $(SRC_DIR)/main.c \
			 $(SRC_DIR)/routines.c \
			 $(SRC_DIR)/generators.c \
			 $(SRC_DIR)/utils/messages.c \
			 $(SRC_DIR)/utils/utils.c \
			 $(SRC_DIR)/utils/routines_utils.c \

OBJ_FILES = $(patsubst $(SRC_DIR)/*/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@

# Make sure dir exists
$(OBJ_FILES): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Create object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@if [ -d "$(OBJ_DIR)" ]; then 		rm -rf $(OBJ_DIR); 	fi

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

