/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 18:27:13 by psalame           #+#    #+#             */
/*   Updated: 2023/12/26 18:46:24 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	get_pid_at_index(int *pids, int index, sem_t *sem_pids)
{
	int	pid;

	sem_wait(sem_pids);
	pid = pids[index];
	sem_post(sem_pids);
	return (pid);
}

void	*wait_any_philo_died(void *data)
{
	int		*pids;
	sem_t	*sem_died;
	sem_t	*sem_pids;

	pids = data;
	sem_died = sem_open(SEMA_DIED, O_RDWR);
	sem_wait(sem_died);
	sem_pids = sem_open(SEMA_PIDS, O_RDWR);
	sem_wait(sem_pids);
	kill_philosophers(pids);
	sem_post(sem_pids);
	sem_close(sem_pids);
	sem_close(sem_died);
	return (NULL);
}

void	*wait_all_philo_ate(void *data)
{
	int		i;
	int		*pids;
	sem_t	*sem_ate;
	sem_t	*sem_pids;

	pids = data;
	sem_ate = sem_open(SEMA_EATEN, O_RDWR);
	sem_pids = sem_open(SEMA_PIDS, O_RDWR);
	i = 0;
	while (get_pid_at_index(pids, i, sem_pids) != 0)
	{
		sem_wait(sem_ate);
		i++;
	}
	sem_wait(sem_pids);
	kill_philosophers(pids);
	sem_post(sem_pids);
	sem_close(sem_pids);
	sem_close(sem_ate);
	return (NULL);
}

void	*wait_all_process_finish(void *data)
{
	int		*pids;
	int		i;
	sem_t	*sem;

	pids = data;
	i = 0;
	sem = sem_open(SEMA_PIDS, O_RDWR);
	while (get_pid_at_index(pids, i, sem) != 0)
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}
	sem_close(sem);
	sem = NULL;
	sem = sem_open(SEMA_DIED, O_RDWR);
	sem_post(sem);
	sem_close(sem);
	sem = sem_open(SEMA_EATEN, O_RDWR);
	sem_post(sem);
	sem_close(sem);
	return (NULL);
}
