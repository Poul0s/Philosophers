# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psalame <psalame@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/04 18:37:48 by psalame           #+#    #+#              #
#    Updated: 2023/12/04 18:51:00 by psalame          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# MAKE VARIABLES

CC 			= cc

CFLAGS 		= -Wall -Wextra -Werror

override CFLAGS = -g

SRC			=	

OBJ			=	$(addprefix obj/, $(SRCS:.c=.o))

OBJ_DIR		=	$(sort $(dir $(OBJ)))

NAME		=	philo

LIBFT_PATH	=	./libft

LIBFT		=	$(LIBFT_PATH)/libft.a

LIBS		=	-lft -L$(LIBFT_PATH)

INCLUDES	=	$(LIBFT_PATH)/header



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
	$(CC) $(CFLAGS) $^ $(INCLUDES) -o $@

$(OBJ_DIR):
	@mkdir -p $@