/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 17:42:23 by psalame           #+#    #+#             */
/*   Updated: 2023/12/11 13:51:12 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	parse_arguments(int ac, char **av, t_simulation_data *data)
{
	data->nb_philosophers = ft_atoi(av[1]);
	if (data->nb_philosophers < 0)
		exit_error();
	data->die_time = ft_atoi(av[2]);
	if (data->die_time < 0)
		exit_error();
	data->eat_time = ft_atoi(av[3]);
	if (data->eat_time < 0)
		exit_error();
	data->sleep_time = ft_atoi(av[4]);
	if (data->sleep_time < 0)
		exit_error();
	if (ac == 6)
	{
		data->nb_meal = ft_atoi(av[5]);
		if (data->nb_meal < 0)
			exit_error();
	}
	else
		data->nb_meal = -1;
}

int	main(int ac, char **av)
{
	t_simulation_data	data;

	if (ac != 5 && ac != 6)
		exit_error();
	parse_arguments(ac, av, &data);
	if (data.nb_philosophers > 0)
		start_simulation(data);
	return (0);
}
