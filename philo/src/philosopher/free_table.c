/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:47:28 by psalame           #+#    #+#             */
/*   Updated: 2023/12/06 15:06:10 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_philosophers(t_philosoph **first)
{
	t_philosoph	*current;
	t_philosoph	*next;

	if (first == NULL)
		return ;
	current = *first;
	while (current != NULL)
	{
		next = current->right;
		if (next == *first)
			next = NULL;
		free(current);
		current = next;
	}
}
