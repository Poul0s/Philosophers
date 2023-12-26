/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 17:46:50 by psalame           #+#    #+#             */
/*   Updated: 2023/12/26 18:47:45 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	init_semaphore(const char *sem_name, int default_value)
{
	sem_t	*sem;

	sem_unlink(sem_name);
	sem = sem_open(sem_name, O_CREAT, 0777, default_value);
	if (sem == SEM_FAILED)
		exit_error();
	sem_close(sem);
}

static void	init_semaphores(t_simulation_data data)
{
	init_semaphore(SEMA_FORKS, data.nb_philosophers);
	init_semaphore(SEMA_PRINT, 1);
	init_semaphore(SEMA_DIED, 0);
	init_semaphore(SEMA_EATEN, 0);
	init_semaphore(SEMA_PIDS, 1);
}

void	start_simulation(t_simulation_data data)
{
	int			*pids;
	pthread_t	thread_died;
	pthread_t	thread_eaten;
	pthread_t	thread_process;

	init_semaphores(data);
	pids = init_philosophers(data);
	pthread_create(&thread_died, NULL, &wait_any_philo_died, pids);
	pthread_create(&thread_eaten, NULL, &wait_all_philo_ate, pids);
	pthread_create(&thread_process, NULL, &wait_all_process_finish, pids);
	pthread_join(thread_process, NULL);
	pthread_join(thread_eaten, NULL);
	pthread_join(thread_died, NULL);
	free(pids);
	sem_unlink(SEMA_FORKS);
	sem_unlink(SEMA_PRINT);
	sem_unlink(SEMA_DIED);
	sem_unlink(SEMA_EATEN);
}
