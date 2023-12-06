/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 19:32:19 by psalame           #+#    #+#             */
/*   Updated: 2023/12/05 19:28:40 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	start_process(t_philosoph *first, pthread_t *threads)
{
	int i = 0;
	while (threads[i])
	{
		pthread_detach(threads[i++]);
	}
	free_threads(threads);
	free_philosophers(&first);
}

void	start_simulation(t_simulation_data data)
{
	t_philosoph	*first;
	t_philosoph	*current;
	pthread_t	*threads;
	int			id;

	first = create_philosophs(data);
	threads = ft_calloc(data.nb_philosophers + 1, sizeof(pthread_t));
	if (!threads)
		exit_error(first, NULL);
	current = first;
	id = 0;
	while (current)
	{
		current->id = ++id;
		if (pthread_create(&threads[id - 1], NULL, &born_philosoph, current))
		{
			threads[id - 1] = 0;
			exit_error(first, threads);
		}
		current = current->right;
		if (current == first)
			current = NULL;
	}
	start_process(first, threads);
}

int	main(int ac, char **av)
{
	t_simulation_data	data;

	if (ac != 5 && ac != 6)
		exit_error(NULL, NULL);
	data.nb_philosophers = ft_atoi(av[1]);
	data.die_time = ft_atoi(av[2]);
	data.eat_time = ft_atoi(av[3]);
	data.sleep_time = ft_atoi(av[4]);
	if (ac == 6)
		data.nb_meal = ft_atoi(av[5]);
	else
		data.nb_meal = -1;
	if (data.nb_philosophers <= 0)
		return (0);
	start_simulation(data);
	return (0);
}
