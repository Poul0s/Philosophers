/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:03:05 by psalame           #+#    #+#             */
/*   Updated: 2023/11/21 16:56:51 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include "ft_string.h"
# include "ft_is.h"
# include "ft_memoryManager.h"
# include "ft_convert.h"
# include "ft_print.h"
# include "ft_linkedList.h"
# include "get_next_line.h"
# define FT_HEXA_BASE "0123456789abcdef"
# define FT_HEXA_BASE_MAJ "0123456789ABCDEF"
# define FT_TEN_BASE "0123456789"
# define FT_BINARY_BASE "01"
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef enum e_bool
{
	FALSE,
	TRUE,
}	t_bool;

#endif
