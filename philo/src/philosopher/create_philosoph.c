/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philosoph.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 23:49:54 by psalame           #+#    #+#             */
/*   Updated: 2023/12/07 18:11:27 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philosoph	*create_philosophs(t_simulation_data data)
{
	t_philosoph	*first;
	t_philosoph	*tmp;
	t_philosoph	*current;
	int			i;

	first = NULL;
	tmp = NULL;
	current = NULL;
	i = 0;
	while (i++ < data.nb_philosophers)
	{
		current = ft_calloc(1, sizeof(t_philosoph));
		if (current == NULL)
			exit_error(first, NULL, data.table_forks);
		if (!first)
			first = current;
		else
			tmp->right = current;
		current->left = tmp;
		tmp = current;
	}
	first->left = current;
	current->right = first;
	return (first);
}
