/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 19:32:48 by psalame           #+#    #+#             */
/*   Updated: 2023/12/07 09:22:26 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	check_dead(t_philosoph *philosoph)
{
	long	current_time;

	current_time = get_program_time();
	if (philosoph->last_meal_date + philosoph->simulation->die_time < current_time)
	{
		philosoph->simulation->active = false;
		print_state(philosoph, current_time);
	}
}

static void	check_end(t_philosoph *philosoph)
{
	t_philosoph	*current;
	bool		all_philosoph_eaten;

	if (philosoph->simulation->nb_meal == -1)
		return ;
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
}

static void	check_eat(t_philosoph *philosoph)
{
	long				current_time;
	t_simulation_data	*data;

	data = philosoph->simulation;
	current_time = get_program_time();
	if (philosoph->state_date + data->eat_time <= current_time)
	{
		philosoph->state = sleeping;
		philosoph->state_date = current_time;
		philosoph->number_meal++;
		print_state(philosoph, current_time);
		check_end(philosoph);
	}
}

static void	check_sleep(t_philosoph *philosoph)
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

static void	check_think(t_philosoph *philosoph)
{
	long				current_time;
	t_philosoph			*left_fork_owner;
	t_philosoph			*right_fork_owner;

	left_fork_owner = NULL;
	right_fork_owner = NULL;
	if (philosoph->right->state != eating)
		right_fork_owner = philosoph;
	if (philosoph->left->state != eating && philosoph->left != philosoph)
		left_fork_owner = philosoph->left;
	if (left_fork_owner && right_fork_owner)
	{
		current_time = get_program_time();
		philosoph->state = eating;
		philosoph->state_date = current_time;
		philosoph->last_meal_date = current_time;
		print_state(philosoph, current_time);
	}
}

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
		check_think(philosoph);
	check_dead(philosoph);
	return (sleep_time);
}

void	*born_philosoph(void *data)
{
	t_philosoph 	*philosoph;
	int				int_min;
	int				sleep_time;

	int_min = -2147483648;
	while (int_min == -int_min)
	{
		philosoph = data;
		while (pthread_mutex_lock(&philosoph->simulation->mutex))
			usleep(10);
		if (!philosoph->simulation->active)
		{
			pthread_mutex_unlock(&philosoph->simulation->mutex);
			return (NULL);
		}
		sleep_time = update_action(philosoph);
		pthread_mutex_unlock(&philosoph->simulation->mutex);
		usleep(sleep_time * 1000);
		// todo take a fork && naybe remove sleep_time from usleep
	}
	return (NULL);
}
