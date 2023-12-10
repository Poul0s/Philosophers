# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psalame <psalame@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/04 18:37:48 by psalame           #+#    #+#              #
#    Updated: 2023/12/10 17:24:46 by psalame          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# MAKE VARIABLES

CC 			= cc

CFLAGS 		= -Wall -Wextra -Werror

override CFLAGS = -g

SRC			=	main.c \
				error.c \
				simulation.c \
				utils/ft_atoi.c \
				utils/time.c \
				philosopher/check_state.c \
				philosopher/forks_manager.c \
				philosopher/init.c \
				philosopher/kill_process.c \
				philosopher/philo_life.c \
				philosopher/print_state.c \

OBJ			=	$(addprefix obj/, $(SRC:.c=.o))

SRC			:=	$(addprefix src/, $(SRC))

OBJ_DIR		=	$(sort $(dir $(OBJ)))

NAME		=	philo_bonus


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