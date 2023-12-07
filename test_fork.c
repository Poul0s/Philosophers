/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 19:09:13 by psalame           #+#    #+#             */
/*   Updated: 2023/12/07 20:05:07 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

void	open_forks(void)
{
	int	pids[8];
	int	parent_pid = getpid();
	for (int i = 0; i < 8; i++)
	{
		int child = fork();
		if (getpid() != parent_pid)
		{
			sem_t *sem = sem_open("AAC", O_RDWR | O_SYNC);
			if (sem == SEM_FAILED)
				printf("failed %s\n", strerror(errno));
			else
			{
				sem_wait(sem);
				printf("yessir\n");
				usleep(1000000);
				sem_post(sem);
			}
			exit(EXIT_SUCCESS);
		}
		else
			pids[i] = child;
	}
	for (int i = 0; i < 8; i++)
	{
		waitpid(pids[i], NULL, 0);
	}
}

int	main(void)
{
	sem_t	*sem = sem_open("AAC", O_CREAT);
	// initialise 5 forks
	if (sem == SEM_FAILED)
	{
		printf("failed main %s\n", strerror(errno));
		return (1);
	}
	for (int i = 0; i < 5; i++)
		sem_post(sem);
	open_forks();
	if (sem_unlink("AAC") != 0)
		printf("failed to remove sem : %s\n", strerror(errno));
	return (0);
}