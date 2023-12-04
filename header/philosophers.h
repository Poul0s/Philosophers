/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 19:03:02 by psalame           #+#    #+#             */
/*   Updated: 2023/12/04 23:51:41 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHOLOSOPHERS_H
# define PHILOSOPHERS_H
# include "libft.h"
# include <stdbool.h>
# include <stdio.h>

typedef struct	s_state
{
	thinking,
	eating,
	sleeping
}	t_state;

typedef struct s_philosoph
{
	t_state				state;
	long				death_time;
	int					number_meal;
	int					id;
	struct s_philosoph	*right;
	struct s_philosoph	*left;
}							t_philosoph;

typedef struct	s_simulation_data
{
	int		nb_philosophers;
	long	die_time;
	long	eat_time;
	long	sleep_time;
	int		nb_meal;
}			t_simulation_data;

// Error managment
void	exit_error();

t_philosoph	*create_philosophs(t_simulation_data data);
void		born_philosoph(t_philosoph *philosoph);

#endif