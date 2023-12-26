/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 19:41:36 by psalame           #+#    #+#             */
/*   Updated: 2023/12/26 17:26:27 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	exit_error(void)
{
	write(2, "Error\n", 6);
	sem_unlink(SEMA_FORKS);
	sem_unlink(SEMA_PRINT);
	sem_unlink(SEMA_DIED);
	sem_unlink(SEMA_EATEN);
	exit(EXIT_FAILURE);
}
