/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 19:32:48 by psalame           #+#    #+#             */
/*   Updated: 2023/12/06 14:32:32 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*born_philosoph(void *data)
{
	t_philosoph *philosoph;
	int	id;

	philosoph = data;
	id = philosoph->id;
	printf("borning %d\n", id);
	if (id == 3)
		philosoph->simulation->active = false;
	if (philosoph->simulation->active)
		printf("Philosopher %d bornt\n", id);
	return (NULL);
}
