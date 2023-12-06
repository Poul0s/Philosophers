/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 19:41:36 by psalame           #+#    #+#             */
/*   Updated: 2023/12/05 18:31:08 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	exit_error(t_philosoph *first, pthread_t *threads)
{
	ft_printf("%fError\n", 2);
	if (first)
		free_philosophers(&first);
	free(threads);
	exit(EXIT_FAILURE);
}
