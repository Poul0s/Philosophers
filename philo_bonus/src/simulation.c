/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 17:46:50 by psalame           #+#    #+#             */
/*   Updated: 2023/12/10 18:21:52 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <errno.h> // todo rm
#include <string.h> // todo rm

static void	init_semaphores(t_simulation_data data)
{
	sem_t	*sem;

	sem_unlink(SEMA_FORKS);
	sem_unlink(SEMA_PRINT);
	sem = sem_open(SEMA_FORKS, O_CREAT, 0777, data.nb_philosophers);
	if (sem == SEM_FAILED)
		exit_error(NULL);
	sem_close(sem);
	sem = sem_open(SEMA_PRINT, O_CREAT, 0777, 1);
	if (sem == SEM_FAILED)
		exit_error(NULL);
	sem_close(sem);
}

static void	*wait_philo_finished(void *data)
{
	sem_t			*sem;
	t_children_pids *children_data;
	int				wstatus;
	int				current_pid;

	children_data = data;
	current_pid = children_data->pids[children_data->current_pid_i];
	waitpid(current_pid, &wstatus, 0);
	children_data->pids[children_data->current_pid_i] = 0;
	if (WEXITSTATUS(wstatus) == EXIT_SUCCESS)
	{
		printf("has finished life\n");
		return (NULL);
	}
	sem = sem_open(SEMA_PRINT, O_RDWR);
	if (sem == SEM_FAILED)
		exit_error(NULL);
	sem_wait(sem);
	kill_philosophers(children_data->pids);
	sem_post(sem);
	sem_close(sem);
	return (NULL);
}

static t_children_pids	**alloc_children_data(int nb_pids)
{
	t_children_pids	**children_data;
	int				i;

	children_data = malloc((nb_pids + 1) * sizeof(t_children_pids *));
	if (children_data == NULL)
		exit_error(NULL);
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

	init_semaphores(data);
	children_data = alloc_children_data(data.nb_philosophers);
	pids = init_philosophers(data, children_data);
	i = 0;
	while (i < data.nb_philosophers)
	{
		pthread_create(&children_data[i]->checker_pthread, NULL, &wait_philo_finished, children_data[i]);
		i++;
	}
	i = 0;
	while (i < data.nb_philosophers)
		pthread_join(children_data[i++]->checker_pthread, NULL);
	i = 0;
	while (children_data[i] != NULL)
		free(children_data[i++]);
	free(children_data);
	free(pids);
	sem_unlink(SEMA_FORKS);
	sem_unlink(SEMA_PRINT);
}
