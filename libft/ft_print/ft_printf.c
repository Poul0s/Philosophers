/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:16:24 by psalame           #+#    #+#             */
/*   Updated: 2023/11/21 22:28:48 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

static ssize_t	ft_printf_percent(char *str, size_t *i, va_list *ap, int *fd)
{
	*i += 1;
	if (str[*i] == 'c' )
		return (ft_putchar_fd(va_arg(*ap, int), *fd));
	if (str[*i] == '%' )
		return (ft_putchar_fd('%', *fd));
	else if (str[*i] == 's')
		return (ft_putstr_fd(va_arg(*ap, char *), *fd));
	else if (str[*i] == 'p')
		return (ft_putptr_fd(va_arg(*ap, void *), *fd));
	else if (str[*i] == 'i' || str[*i] == 'd')
		return (ft_putnbr_fd(va_arg(*ap, int), *fd));
	else if (str[*i] == 'u')
		return (ft_putunbr_fd(va_arg(*ap, unsigned int), *fd));
	else if (str[*i] == 'x' || str[*i] == 'X')
		return (ft_putxnbr_fd(va_arg(*ap, unsigned int), str[*i] == 'X', *fd));
	else if (str[*i] == 'f')
	{
		*fd = va_arg(*ap, int);
		return (0);
	}
	else
	{
		*i -= 1;
		return (ft_putchar_fd('%', *fd));
	}
}

ssize_t	ft_printf(const char *str, ...)
{
	size_t	i;
	size_t	strlen;
	ssize_t	res_str_len;
	va_list	ap;
	int		fd;

	va_start(ap, str);
	i = 0;
	strlen = ft_strlen((char *)str);
	res_str_len = 0;
	fd = 1;
	while (i < strlen)
	{
		if (str[i] == '%')
			res_str_len += ft_printf_percent((char *)str, &i, &ap, &fd);
		else
		{
			res_str_len++;
			ft_putchar_fd(str[i], fd);
		}
		i++;
	}
	va_end(ap);
	return (res_str_len);
}
