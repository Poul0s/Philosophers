/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 19:41:36 by psalame           #+#    #+#             */
/*   Updated: 2023/12/10 15:10:06 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	exit_error(t_children_pids **children_data)
{
	int	i;

	i = 0;
	write(2, "Error\n", 6);
	if (children_data != NULL)
	{
		while (children_data[i] != NULL)
			free(children_data[i++]);
		free(children_data);
	}
	sem_unlink(SEMA_FORKS);
	sem_unlink(SEMA_PRINT);
	exit(EXIT_FAILURE);
}
