# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aduban <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/02 12:05:34 by aduban            #+#    #+#              #
#    Updated: 2016/04/29 16:32:16 by aduban           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = mymalloc.so

SRC = malloc.c\
	  realloc.c\
	  free.c\
	  getsetters.c\
	  large_getsetters.c\
	  large_malloc.c\
	  show_mem.c\
	  small_malloc.c

.PHONY: libft.a

OBJ = $(SRC:.c=.o)

all : libft.a $(NAME)

libft.a:
		@$(MAKE) -C ./libft

$(NAME) : $(OBJ)
		@gcc -Wall -Werror -Wextra -shared -o $(NAME) $(SRC) -L./libft/ -lftprintf -I ./libft

%.o: %.c
		@gcc -Wall -Werror -Wextra -I./libft/ -o $@ -c $^

clean :
		rm -f $(OBJ)

fclean : clean
		rm -f $(NAME)

re : fclean all
