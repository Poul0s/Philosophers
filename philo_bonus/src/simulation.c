/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 17:46:50 by psalame           #+#    #+#             */
/*   Updated: 2023/12/09 15:12:45 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	init_semaphores(t_simulation_data data)
{
	sem_t	*sem;

	sem_unlink(SEMA_FORKS);
	sem_unlink(SEMA_PRINT);
	sem = sem_open(SEMA_FORKS, O_CREAT, 0777, data.nb_meal); // todo check what happen if set at 0644
	if (sem == SEM_FAILED)
		exit_error();
	sem_close(sem);
	sem = sem_open(SEMA_PRINT, O_CREAT, 0777, 1);
	if (sem == SEM_FAILED)
		exit_error();
	sem_close(sem);
}

static void	wait_philo_finished(int *pids)
{
	
}

static t_children_pids	**alloc_children_data(int nb_pids)
{
	t_children_pids	**children_data;
	int				i;

	children_data = malloc((nb_pids + 1) * sizeof(t_children_pids *));
	if (children_data == NULL)
		exit_error();
	children_data[nb_pids] = NULL;
	i = 0;
	while (i < nb_pids)
	{
		children_data[i] = malloc(sizeof(t_children_pids));
		if (children_data[i] == NULL)
			exit_error(children_data);
		i++;
	}
	return (children_data);
}

void	start_simulation(t_simulation_data data)
{
	int				*pids;
	t_children_pids	**children_data;
	int				i;

	children_data = alloc_children_data(data.nb_philosophers); // todo add to exit_error for free it
	init_semaphores(data);
	pids = init_philosophers(data);
	i = 0;
	while (i < data.nb_philosophers)
	{
		children_data[i]->current_pid = pids[i];
		children_data[i]->pids = pids;
		i++;
	}
	// wait each children in thread 
		// x-> if one exit : kill all other childrens
	// so join threads
	// then free children_data
	sem_unlink(SEMA_FORKS);
	sem_unlink(SEMA_PRINT);
}
