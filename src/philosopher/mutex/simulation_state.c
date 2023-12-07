/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_state.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:56:44 by psalame           #+#    #+#             */
/*   Updated: 2023/12/07 14:26:10 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	get_simulation_state(t_simulation_data *data)
{
	bool	res;
	pthread_mutex_lock(&data->mutex);
		// usleep(1);
	res = data->active;
	pthread_mutex_unlock(&data->mutex);
	return (res);
}

void	set_simulation_state(t_simulation_data *data, bool state)
{
	pthread_mutex_lock(&data->mutex);
		// usleep(1);
	data->active = state;
	pthread_mutex_unlock(&data->mutex);
}

