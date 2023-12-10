/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 16:51:29 by psalame           #+#    #+#             */
/*   Updated: 2023/12/10 18:25:20 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*take_forks(void *data)
{
	t_philosoph *philosoph;
	sem_t		*sem;
	char		i;

	philosoph = data;
	i = 0;
	sem = sem_open(SEMA_FORKS, O_RDWR);
	while (i < 2)
	{
		sem_wait(sem);
		philosoph->number_forks++;
		print_fork_taken(philosoph, get_program_time());
		i++;
	}
	sem_close(sem);
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
