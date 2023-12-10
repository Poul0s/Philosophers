/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:34:28 by psalame           #+#    #+#             */
/*   Updated: 2023/12/10 17:33:38 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_state(t_philosoph *philosoph, long time)
{
	sem_t	*sem;

	sem = sem_open(SEMA_PRINT, O_RDWR);
	sem_wait(sem);
	if (philosoph->last_meal_date + philosoph->simulation_data.die_time < time)
		printf("%ld %d died\n", time, philosoph->id);
	else
	{
		if (philosoph->state == eating)
			printf("%ld %d is eating\n", time, philosoph->id);
		else if (philosoph->state == sleeping)
			printf("%ld %d is sleeping\n", time, philosoph->id);
		else
			printf("%ld %d is thinking\n", time, philosoph->id);
	}
	sem_post(sem);
	sem_close(sem);
}

void	print_fork_taken(t_philosoph *philosoph, long time)
{
	sem_t	*sem;

	sem = sem_open(SEMA_PRINT, O_RDWR);
	sem_wait(sem);
	printf("%ld %d has taken a fork\n", time, philosoph->id);
	sem_post(sem);
	sem_close(sem);
}
