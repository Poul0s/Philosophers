/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:27:05 by psalame           #+#    #+#             */
/*   Updated: 2023/12/14 16:51:21 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_dead(t_philosoph *philosoph)
{
	long	current_time;
	long	last_meal_date;
	long	die_time;

	current_time = get_program_time();
	last_meal_date = philosoph->last_meal_date;
	die_time = philosoph->simulation->die_time;
	if (last_meal_date + die_time < current_time)
		print_state(philosoph, current_time);
}

void	check_end(t_philosoph *philosoph)
{
	t_philosoph	*current;
	bool		all_philosoph_eaten;

	if (philosoph->simulation->nb_meal == -1)
		return ;
	pthread_mutex_lock(&philosoph->simulation->mutex);
	all_philosoph_eaten = true;
	current = philosoph;
	while (current)
	{
		if (current->number_meal < philosoph->simulation->nb_meal)
		{
			all_philosoph_eaten = false;
			break ;
		}
		current = current->right;
		if (current == philosoph)
			current = NULL;
	}
	if (all_philosoph_eaten)
		philosoph->simulation->active = false;
	pthread_mutex_unlock(&philosoph->simulation->mutex);
}

void	check_eat(t_philosoph *philosoph)
{
	long				current_time;
	t_simulation_data	*data;

	data = philosoph->simulation;
	current_time = get_program_time();
	if (philosoph->state_date + data->eat_time <= current_time)
	{
		philosoph->state = sleeping;
		philosoph->state_date = current_time;
		pthread_mutex_lock(&data->mutex);
		philosoph->number_meal++;
		pthread_mutex_unlock(&data->mutex);
		print_state(philosoph, current_time);
		release_forks(philosoph->id - 1, philosoph->simulation);
		check_end(philosoph);
	}
}

void	check_sleep(t_philosoph *philosoph)
{
	long				current_time;
	t_simulation_data	*data;

	data = philosoph->simulation;
	current_time = get_program_time();
	if (philosoph->state_date + data->sleep_time <= current_time)
	{
		philosoph->state = thinking;
		philosoph->state_date = current_time;
		print_state(philosoph, current_time);
	}
}

void	check_think(t_philosoph *philosoph)
{
	long	current_time;

	if (try_take_forks(philosoph->id - 1, philosoph->simulation))
	{
		current_time = get_program_time();
		philosoph->state = eating;
		philosoph->state_date = current_time;
		philosoph->last_meal_date = current_time;
		print_state(philosoph, current_time);
	}
}
