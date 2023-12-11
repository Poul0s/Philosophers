/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 17:46:50 by psalame           #+#    #+#             */
/*   Updated: 2023/12/11 16:01:54 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	init_semaphores(t_simulation_data data)
{
	sem_t	*sem;

	sem_unlink(SEMA_FORKS);
	sem_unlink(SEMA_PRINT);
	sem_unlink(SEMA_DIED);
	sem_unlink(SEMA_EATEN);
	sem = sem_open(SEMA_FORKS, O_CREAT, 0777, data.nb_philosophers);
	if (sem == SEM_FAILED)
		exit_error();
	sem_close(sem);
	sem = sem_open(SEMA_PRINT, O_CREAT, 0777, 1);
	if (sem == SEM_FAILED)
		exit_error();
	sem_close(sem);
	sem = sem_open(SEMA_DIED, O_CREAT, 0777, 0);
	if (sem == SEM_FAILED)
		exit_error();
	sem_close(sem);
	sem = sem_open(SEMA_EATEN, O_CREAT, 0777, 0);
	if (sem == SEM_FAILED)
		exit_error();
	sem_close(sem);
}

void	*wait_any_philo_died(void *data)
{
	int		*pids;
	sem_t	*sem;

	pids = data;
	sem = sem_open(SEMA_DIED, O_RDWR);
	sem_wait(sem);
	kill_philosophers(pids);
	sem_close(sem);
	return (NULL);
}

void	*wait_all_philo_ate(void *data)
{
	int		i;
	int		*pids;
	sem_t	*sem;

	pids = data;
	sem = sem_open(SEMA_EATEN, O_RDWR);
	i = 0;
	while (pids[i++] != 0)
		sem_wait(sem);
	kill_philosophers(pids);
	sem_close(sem);
	return (NULL);
}

void	*wait_all_process_finish(void *data)
{
	int		*pids;
	int		i;
	sem_t	*sem;

	pids = data;
	i = 0;
	while (pids[i++])
		waitpid(pids[i], NULL, 0);
	sem = sem_open(SEMA_DIED, O_RDWR);
	sem_post(sem);
	sem_close(sem);
	sem = sem_open(SEMA_EATEN, O_RDWR);
	sem_post(sem);
	sem_close(sem);
	return (NULL);
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
