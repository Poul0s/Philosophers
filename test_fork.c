/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 19:09:13 by psalame           #+#    #+#             */
/*   Updated: 2023/12/08 17:02:25 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#define SEMA_NAME "sema"

void	open_forks(void)
{
	int	pids[8];
	int	parent_pid = getpid();
	for (int i = 0; i < 8; i++)
	{
		int child = fork();
		if (getpid() != parent_pid)
		{
			sem_t *sem = sem_open(SEMA_NAME, O_RDWR);
			if (sem == SEM_FAILED)
				printf("failed %s\n", strerror(errno));
			else
			{
				if (sem_wait(sem) != 0)
					printf("error : %s\n", strerror(errno));
				else
					printf("yessir\n");
				usleep(1000000);
				sem_post(sem);
				sem_close(sem);
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
	sem_unlink(SEMA_NAME);
	sem_t	*sem = sem_open(SEMA_NAME, O_CREAT, 0777, 2);
	if (sem == SEM_FAILED)
	{
		printf("failed main %s\n", strerror(errno));
		return (1);
	}
	if (sem_close(sem) != 0)
		printf("error on closing : %s\n", strerror(errno));
	open_forks();
	if (sem_unlink(SEMA_NAME) != 0)	printf("second\n");

	return (0);
}