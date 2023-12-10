/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 15:48:31 by psalame           #+#    #+#             */
/*   Updated: 2023/12/10 17:03:53 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static long	update_action(t_philosoph *philosoph)
{
	long	sleep_time;

	sleep_time = 1;
	if (philosoph->state == eating)
		check_eat(philosoph);
	else if (philosoph->state == sleeping)
	{
		check_sleep(philosoph);
		if (philosoph->state == thinking)
			sleep_time = 2;
	}
	else if (philosoph->state == thinking)
	{
		check_think(philosoph);
		if (philosoph->state == thinking)
			sleep_time = 0;
	}
	check_dead(philosoph);
	return (sleep_time);
}

void	start_philosopher_process(t_philosoph philosoph)
{
	int	sleep_time;

	print_state(&philosoph, 0);
	wait_available_forks(&philosoph);
	while (1)
	{
		sleep_time = update_action(&philosoph);
		usleep(sleep_time * 1000);
	}
}
