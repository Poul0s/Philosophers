/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:34:28 by psalame           #+#    #+#             */
/*   Updated: 2023/12/07 15:04:10 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_state(t_philosoph *philosoph, long time)
{
	pthread_mutex_lock(&philosoph->simulation->mutex);
	if (philosoph->last_meal_date + philosoph->simulation->die_time < time)
		printf("%ld %d died\n", time, philosoph->id);
	else if (philosoph->simulation->active)
	{
		if (philosoph->state == eating)
		{
			printf("%ld %d has taken a fork\n", time, philosoph->id);
			printf("%ld %d has taken a fork\n", time, philosoph->id);
			printf("%ld %d is eating\n", time, philosoph->id);
		}
		else if(philosoph->state == sleeping)
			printf("%ld %d is sleeping\n", time, philosoph->id);
		else
			printf("%ld %d is thinking\n", time, philosoph->id);
	}
	pthread_mutex_unlock(&philosoph->simulation->mutex);
}
