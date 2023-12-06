# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psalame <psalame@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/04 18:37:48 by psalame           #+#    #+#              #
#    Updated: 2023/12/05 19:22:16 by psalame          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# MAKE VARIABLES

CC 			= cc

CFLAGS 		= -Wall -Wextra -Werror

override CFLAGS = -g

SRC			=	main.c \
				error.c \
				philosopher/create_philosoph.c \
				philosopher/free_table.c \
				philosopher/philosopher.c \
				free_threads.c \

OBJ			=	$(addprefix obj/, $(SRC:.c=.o))

SRC			:=	$(addprefix src/, $(SRC))

OBJ_DIR		=	$(sort $(dir $(OBJ)))

NAME		=	philo

LIBFT_PATH	=	./libft

LIBFT		=	$(LIBFT_PATH)/libft.a

LIBS		=	-lft -L$(LIBFT_PATH) -lpthread

INCLUDES	=	-I$(LIBFT_PATH)/header -I./header



# MAIN FUNCTIONS

all: $(NAME)

clean:
	make -C $(LIBFT_PATH) clean
	rm -rf obj
fclean: clean
	make -C $(LIBFT_PATH) fclean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re



# COMPLEMENTARY FUNCTIONS

$(LIBFT):
	make -C $(LIBFT_PATH)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

obj/%.o: %.c
	$(CC) $(CFLAGS) -c $^ $(INCLUDES) -o $@

$(OBJ_DIR):
	@mkdir -p $@