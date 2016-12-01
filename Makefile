# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aduban <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/02 12:05:34 by aduban            #+#    #+#              #
#    Updated: 2016/12/01 17:35:28 by aduban           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif


CC=clang
FLAGS=-Wall -Wextra -Werror

NAME=libft_malloc_$(HOSTTYPE).so

LIBS_DIR=./libs
DIR_PRINTF=$(LIBS_DIR)/printf
DIR_LIBFT=$(LIBS_DIR)/libft

LIBS=-L $(DIR_PRINTF) -lprintf -L $(DIR_LIBFT) -lft

SRC_DIR=srcs
INCLUDES=-I ./ -I ./includes -I $(DIR_PRINTF) -I $(DIR_LIBFT)

BUILD_DIR= __build


SRC = malloc.c\
	  realloc.c\
	  free.c\
	  getsetters.c\
	  large_getsetters.c\
	  large_malloc.c\
	  show_mem.c\
	  small_malloc.c \
	  handle_limit.c \
	  utils.c


OBJ=$(addprefix $(BUILD_DIR)/,$(SRC:.c=.o))

all:$(BUILD_DIR) $(NAME)

$(BUILD_DIR):
	@mkdir -p $@

exec:
	@make -C $(DIR_LIBFT)
	@make -C $(DIR_PRINTF)

$(BUILD_DIR)/%.o:$(SRC_DIR)/%.c
	@$(CC) $(FLAGS) -fPIC -c $< -o $@ $(INCLUDES)

$(NAME):exec $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) $(LIBS) -shared -o $@
	@echo "$@ was created"
	@ln -f -s libft_malloc_$(HOSTTYPE).so libft_malloc.so

clean:
	@rm -rf $(BUILD_DIR)
	@rm -f libft_malloc.so

fclean: clean
	@rm -f $(NAME) $(TEST)
	@make $@ -C $(DIR_LIBFT)
	@make $@ -C $(DIR_PRINTF)

re: fclean all
