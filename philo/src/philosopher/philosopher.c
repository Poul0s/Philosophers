/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 19:32:48 by psalame           #+#    #+#             */
/*   Updated: 2023/12/07 15:27:45 by psalame          ###   ########.fr       */
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

void	*born_philosoph(void *data)
{
	t_philosoph		*philosoph;
	int				int_min;
	int				sleep_time;

	int_min = -2147483648;
	while (int_min == -int_min)
	{
		philosoph = data;
		if (!get_simulation_state(philosoph->simulation))
			return (NULL);
		sleep_time = update_action(philosoph);
		usleep(sleep_time * 1000);
	}
	return (NULL);
}
