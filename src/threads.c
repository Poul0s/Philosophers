/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:33:29 by psalame           #+#    #+#             */
/*   Updated: 2023/12/06 17:33:34 by psalame          ###   ########.fr       */
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

// todo send pointer of *threads
void	init_threads(pthread_t **threads, t_philosoph *first, t_simulation_data *data)
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
			exit_error(first, *threads);
		}
		current = current->right;
		if (current == first)
			current = NULL;
	}
}

void	start_simulation(t_simulation_data data)
{
	t_philosoph		*first;
	pthread_t		*threads;

	first = create_philosophs(data);
	if (pthread_mutex_init(&data.mutex, NULL))
		exit_error(first, NULL);
	threads = ft_calloc(data.nb_philosophers + 1, sizeof(pthread_t));
	if (!threads)
		exit_error(first, NULL);
	get_program_time();
	init_threads(&threads, first, &data);
	join_threads(threads);
	free_philosophers(&first);
}
