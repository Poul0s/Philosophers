/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 19:41:36 by psalame           #+#    #+#             */
/*   Updated: 2023/12/07 15:17:56 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	exit_error(t_philosoph *first, pthread_t *threads, t_fork *forks)
{
	write(2, "Error\n", 6);
	if (first)
		free_philosophers(&first);
	free(threads);
	free(forks);
	exit(EXIT_FAILURE);
}
