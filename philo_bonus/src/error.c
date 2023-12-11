/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 19:41:36 by psalame           #+#    #+#             */
/*   Updated: 2023/12/11 13:51:01 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	exit_error(void)
{
	int	i;

	i = 0;
	write(2, "Error\n", 6);
	sem_unlink(SEMA_FORKS);
	sem_unlink(SEMA_PRINT);
	exit(EXIT_FAILURE);
}
