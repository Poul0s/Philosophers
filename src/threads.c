/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:33:29 by psalame           #+#    #+#             */
/*   Updated: 2023/12/07 18:08:52 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	join_threads(pthread_t *threads)
{
	int	i;

	i = 0;
	while (threads[i])
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	free(threads);
}

void	init_threads(pthread_t **threads, \
					t_philosoph *first, \
					t_simulation_data *data)
{
	t_philosoph	*current;
	int			id;

	current = first;
	id = 0;
	while (current)
	{
		current->id = ++id;
		current->simulation = data;
		if (pthread_create(&(*threads)[id - 1], NULL, &born_philosoph, current))
		{
			(*threads)[id - 1] = 0;
			exit_error(first, *threads, data->table_forks);
		}
		current = current->right;
		if (current == first)
			current = NULL;
	}
}

static void	init_forks(t_simulation_data *data)
{
	int	i;

	data->table_forks = ft_calloc(data->nb_philosophers, sizeof(t_fork));
	if (!data->table_forks)
		exit_error(NULL, NULL, NULL);
	i = 0;
	while (i < data->nb_philosophers)
	{
		if (pthread_mutex_init(&data->table_forks[i].mutex, NULL))
			exit_error(NULL, NULL, data->table_forks);
		i++;
	}
}

void	start_simulation(t_simulation_data data)
{
	t_philosoph		*first;
	pthread_t		*threads;

	init_forks(&data);
	first = create_philosophs(data);
	if (pthread_mutex_init(&data.mutex, NULL))
		exit_error(first, NULL, data.table_forks);
	threads = ft_calloc(data.nb_philosophers + 1, sizeof(pthread_t));
	if (!threads)
		exit_error(first, NULL, data.table_forks);
	get_program_time();
	init_threads(&threads, first, &data);
	join_threads(threads);
	free_philosophers(&first);
	free(data.table_forks);
}
