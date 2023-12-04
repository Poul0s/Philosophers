/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 19:32:19 by psalame           #+#    #+#             */
/*   Updated: 2023/12/04 23:57:03 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	start_simulation(t_simulation_data data)
{
	t_philosoph	*first;

	first = create_philosophs(data);
}

int	main(int ac, char **av)
{
	t_simulation_data	data;

	if (ac != 5 && ac != 6)
		exit_error();
	data.nb_philosophers = ft_atoi(av[1]);
	data.die_time = ft_atoi(av[2]);
	data.eat_time = ft_atoi(av[3]);
	data.sleep_time = ft_atoi(av[4]);
	if (ac == 6)
		data.nb_meal = ft_atoi(av[5]);
	else
		data.nb_meal = -1;
	if (data.nb_philosophers <= 0)
		return (0);
	start_simulation(data);
	return (0);
}
