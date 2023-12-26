/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:27:05 by psalame           #+#    #+#             */
/*   Updated: 2023/12/26 17:27:13 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

char	check_dead(t_philosoph *philosoph)
{
	long	current_time;
	long	last_meal_date;
	long	die_time;
	sem_t	*sem;

	current_time = get_program_time();
	last_meal_date = philosoph->last_meal_date;
	die_time = philosoph->simulation_data.die_time;
	if (last_meal_date + die_time < current_time)
	{
		print_state(philosoph, current_time);
		sem = sem_open(SEMA_DIED, O_RDWR);
		sem_post(sem);
		sem_close(sem);
		return (1);
	}
	else
		return (0);
}

void	check_end(t_philosoph *philosoph)
{
	sem_t	*sem;

	if (philosoph->simulation_data.nb_meal == -1)
		return ;
	if (philosoph->number_meal == philosoph->simulation_data.nb_meal)
	{
		sem = sem_open(SEMA_EATEN, O_RDWR);
		sem_post(sem);
		sem_close(sem);
	}
}

void	check_eat(t_philosoph *philosoph)
{
	long				current_time;
	t_simulation_data	data;

	data = philosoph->simulation_data;
	current_time = get_program_time();
	if (philosoph->state_date + data.eat_time <= current_time)
	{
		philosoph->state = sleeping;
		philosoph->state_date = current_time;
		philosoph->number_meal++;
		print_state(philosoph, current_time);
		put_forks_back(philosoph);
		check_end(philosoph);
	}
}

void	check_sleep(t_philosoph *philosoph)
{
	long				current_time;
	t_simulation_data	data;

	data = philosoph->simulation_data;
	current_time = get_program_time();
	if (philosoph->state_date + data.sleep_time <= current_time)
	{
		philosoph->state = thinking;
		philosoph->state_date = current_time;
		wait_available_forks(philosoph);
		print_state(philosoph, current_time);
	}
}

void	check_think(t_philosoph *philosoph)
{
	sem_t	*sem;
	long	current_time;

	sem = sem_open(SEMA_PRINT, O_RDWR);
	sem_wait(sem);
	if (philosoph->number_forks == 2)
	{
		current_time = get_program_time();
		philosoph->state = eating;
		philosoph->state_date = current_time;
		philosoph->last_meal_date = current_time;
		sem_post(sem);
		print_state(philosoph, current_time);
	}
	else
		sem_post(sem);
	sem_close(sem);
}
