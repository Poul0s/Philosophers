/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 17:46:50 by psalame           #+#    #+#             */
/*   Updated: 2023/12/08 18:59:38 by psalame          ###   ########.fr       */
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

void	start_simulation(t_simulation_data data)
{
	init_semaphores(data);
	// todo create philo with fork
	   // on function create philo: create main philo in var and set the philo id for each + fork 
	      // -> then if children continue with philo runtine else continue main process
	// wait each children in thread 
	   // x-> if one exit : kill all other childrens
	// so join threads
	// its end lol
	sem_unlink(SEMA_FORKS);
	sem_unlink(SEMA_PRINT);
}