/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:42:27 by psalame           #+#    #+#             */
/*   Updated: 2023/12/05 19:23:53 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_threads(pthread_t *threads)
{
	int	i;

	i = 0;
	while (threads[i])
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	free(threads);
}
