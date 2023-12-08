/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_access_parent_mem.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 17:23:34 by psalame           #+#    #+#             */
/*   Updated: 2023/12/08 17:31:47 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int	main(void)
{
	char	*str;

	str = malloc(3);
	str[0] = 'a';
	str[1] = 'b';
	str[2] = '\0';
	int child = fork();
	printf("%s\n", str);
	if (getpid() != child)
	{
		waitpid(child, NULL, 0);
	}
	free(str);
	return (0);
}