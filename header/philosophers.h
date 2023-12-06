/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 19:03:02 by psalame           #+#    #+#             */
/*   Updated: 2023/12/06 14:34:26 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>

typedef enum e_state
{
	thinking,
	eating,
	sleeping
}	t_state;

typedef struct s_simulation_data
{
	int		nb_philosophers;
	long	die_time;
	long	eat_time;
	long	sleep_time;
	int		nb_meal;
	bool	active;
}			t_simulation_data;

typedef struct s_philosoph
{
	t_state				state;
	int					number_meal;
	int					id;
	struct s_philosoph	*right;
	struct s_philosoph	*left;
	t_simulation_data	*simulation;
}						t_philosoph;

// utils
void		*ft_calloc(size_t nmemb, size_t size);
int			ft_atoi(const char *nptr);

// Error managment
void		exit_error(t_philosoph *first, pthread_t *thread);

t_philosoph	*create_philosophs(t_simulation_data data);
void		free_philosophers(t_philosoph **first);
void		*born_philosoph(void *data);
void		start_simulation(t_simulation_data data);

#endif