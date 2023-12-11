# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psalame <psalame@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/04 18:37:48 by psalame           #+#    #+#              #
#    Updated: 2023/12/11 16:02:43 by psalame          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# MAKE VARIABLES

CC 			= cc

CFLAGS 		= -Wall -Wextra -Werror

SRC			=	main.c \
				error.c \
				threads.c \
				utils/ft_atoi.c \
				utils/ft_calloc.c \
				utils/time.c \
				philosopher/mutex/forks.c \
				philosopher/mutex/simulation_state.c \
				philosopher/check_state.c \
				philosopher/create_philosoph.c \
				philosopher/free_table.c \
				philosopher/philosopher.c \
				philosopher/print_state.c \

OBJ			=	$(addprefix obj/, $(SRC:.c=.o))

SRC			:=	$(addprefix src/, $(SRC))

OBJ_DIR		=	$(sort $(dir $(OBJ)))

NAME		=	philo


LIBS		=	-lpthread

INCLUDES	=	-I./header



# MAIN FUNCTIONS

all: $(NAME)

clean:
	rm -rf obj
fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re



# COMPLEMENTARY FUNCTIONS

$(NAME): $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

obj/%.o: %.c
	$(CC) $(CFLAGS) -c $^ $(INCLUDES) -o $@

$(OBJ_DIR):
	@mkdir -p $@
