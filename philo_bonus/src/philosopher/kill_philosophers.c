/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 11:56:53 by psalame           #+#    #+#             */
/*   Updated: 2023/12/26 18:36:12 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	kill_philosophers(int *pids)
{
	int	i;

	i = 0;
	while (pids[i] != 0)
	{
		kill(pids[i], SIGKILL);
		pids[i] = 0;
		i++;
	}
}
