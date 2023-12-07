/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:40:21 by psalame           #+#    #+#             */
/*   Updated: 2023/12/07 14:29:57 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	try_take_forks(int fork_a_id, t_simulation_data *data)
{
	int		fork_b_id;
	bool	res;

	fork_b_id = fork_a_id - 1;
	if (fork_a_id == 0)
		fork_b_id = data->nb_philosophers - 1;
	if (fork_a_id == fork_b_id)
		return (false);
	pthread_mutex_lock(&(data->table_forks[fork_a_id].mutex));
	pthread_mutex_lock(&(data->table_forks[fork_b_id].mutex));
	res = true;
	if (data->table_forks[fork_a_id].taken || 
			data->table_forks[fork_b_id].taken)
		res = false;
	if (res)
	{
		data->table_forks[fork_a_id].taken = true;	
		data->table_forks[fork_b_id].taken = true;	
	}
	pthread_mutex_unlock(&(data->table_forks[fork_a_id].mutex));
	pthread_mutex_unlock(&(data->table_forks[fork_b_id].mutex));
	return (res);
}

void	release_forks(int fork_a_id, t_simulation_data *data)
{
	int		fork_b_id;

	fork_b_id = fork_a_id - 1;
	if (fork_a_id == 0)
		fork_b_id = data->nb_philosophers - 1;
	if (fork_a_id == fork_b_id)
		return ;
	pthread_mutex_lock(&(data->table_forks[fork_a_id].mutex));
	pthread_mutex_lock(&(data->table_forks[fork_b_id].mutex));
	data->table_forks[fork_a_id].taken = false;	
	data->table_forks[fork_b_id].taken = false;
	pthread_mutex_unlock(&(data->table_forks[fork_a_id].mutex));
	pthread_mutex_unlock(&(data->table_forks[fork_b_id].mutex));
}
