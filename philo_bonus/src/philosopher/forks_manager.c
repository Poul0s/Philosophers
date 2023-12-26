/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 16:51:29 by psalame           #+#    #+#             */
/*   Updated: 2023/12/26 17:23:37 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*take_forks(void *data)
{
	t_philosoph	*philosoph;
	sem_t		*sem_fork;
	sem_t		*sem_var;
	char		i;

	philosoph = data;
	i = 0;
	sem_fork = sem_open(SEMA_FORKS, O_RDWR);
	sem_var = sem_open(SEMA_PRINT, O_RDWR);
	while (i < 2)
	{
		sem_wait(sem_fork);
		sem_wait(sem_var);
		philosoph->number_forks++;
		sem_post(sem_var);
		print_fork_taken(philosoph, get_program_time());
		i++;
	}
	sem_close(sem_fork);
	sem_close(sem_var);
	return (NULL);
}

void	wait_available_forks(t_philosoph *philosoph)
{
	pthread_t	thread;

	pthread_create(&thread, NULL, &take_forks, philosoph);
	pthread_detach(thread);
}

void	put_forks_back(t_philosoph *philosoph)
{
	sem_t	*sem;

	sem = sem_open(SEMA_FORKS, O_RDWR);
	sem_post(sem);
	sem_post(sem);
	philosoph->number_forks = 0;
	sem_close(sem);
}
