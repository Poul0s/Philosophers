/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 11:37:19 by psalame           #+#    #+#             */
/*   Updated: 2023/12/11 13:51:45 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	born_philosoph(t_philosoph philosoph)
{
	int			child_pid;

	child_pid = fork();
	if (child_pid == 0)
	{
		philosoph.state = thinking;
		philosoph.state_date = get_program_time();
		philosoph.last_meal_date = philosoph.state_date;
		philosoph.number_meal = 0;
		philosoph.number_forks = 0;
		start_philosopher_process(philosoph);
		exit(EXIT_SUCCESS);
		return (0);
	}
	else
		return (child_pid);
}

int	*init_philosophers(t_simulation_data data)
{
	int			*pids;
	int			i;
	t_philosoph	philosoph;

	philosoph.simulation_data = data;
	pids = malloc((data.nb_philosophers + 1) * sizeof(int));
	pids[data.nb_philosophers] = 0;
	if (pids == NULL)
		exit_error();
	i = 0;
	while (i < data.nb_philosophers)
	{
		philosoph.id = i + 1;
		pids[i] = born_philosoph(philosoph);
		if (pids[i] == -1)
		{
			pids[i] = 0;
			kill_philosophers(pids);
			exit_error();
		}
		i++;
	}
	return (pids);
}
