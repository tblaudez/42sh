/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_numeric.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trponess <trponess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 17:16:29 by tblaudez          #+#    #+#             */
/*   Updated: 2018/12/09 00:31:41 by trponess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

char	*get_decimal(va_list ap)
{
	t_printf	*list;

	list = get_list_printf(0);
	if (!list->modif)
		return (ft_itoa(va_arg(ap, int)));
	else if (list->modif & 1)
		return (ft_itoa(va_arg(ap, long)));
	else if (list->modif & (1 << 1))
		return (ft_itoa(va_arg(ap, ssize_t)));
	else if (list->modif & (1 << 2))
		return (ft_itoa(va_arg(ap, int)));
	else if (list->modif & (1 << 3))
		return (ft_itoa((short)va_arg(ap, int)));
	else if (list->modif & (1 << 4))
		return (ft_itoa((signed char)va_arg(ap, int)));
	else if (list->modif & (1 << 5))
		return (ft_itoa(va_arg(ap, long long)));
	return (NULL);
}

char	*get_hexa(va_list ap)
{
	t_printf	*list;

	list = get_list_printf(0);
	if (!list->modif)
		return (ft_uitoabase(va_arg(ap, unsigned int), 16));
	else if (list->modif & 1)
		return (ft_uitoabase(va_arg(ap, unsigned long), 16));
	else if (list->modif & (1 << 1))
		return (ft_uitoabase(va_arg(ap, size_t), 16));
	else if (list->modif & (1 << 2))
		return (ft_uitoabase(va_arg(ap, unsigned int), 16));
	else if (list->modif & (1 << 3))
		return (ft_uitoabase((unsigned short)va_arg(ap, int), 16));
	else if (list->modif & (1 << 4))
		return (ft_uitoabase((unsigned char)va_arg(ap, int), 16));
	else if (list->modif & (1 << 5))
		return (ft_uitoabase(va_arg(ap, unsigned long long), 16));
	return (NULL);
}

char	*get_octal(va_list ap)
{
	t_printf	*list;

	list = get_list_printf(0);
	if (!list->modif)
		return (ft_uitoabase(va_arg(ap, unsigned int), 8));
	else if (list->modif & 1)
		return (ft_uitoabase(va_arg(ap, unsigned long), 8));
	else if (list->modif & (1 << 1))
		return (ft_uitoabase(va_arg(ap, size_t), 8));
	else if (list->modif & (1 << 2))
		return (ft_uitoabase(va_arg(ap, unsigned int), 8));
	else if (list->modif & (1 << 3))
		return (ft_uitoabase((unsigned short)va_arg(ap, int), 8));
	else if (list->modif & (1 << 4))
		return (ft_uitoabase((unsigned char)va_arg(ap, int), 8));
	else if (list->modif & (1 << 5))
		return (ft_uitoabase(va_arg(ap, unsigned long long), 8));
	return (NULL);
}

char	*get_unsigned(va_list ap)
{
	t_printf	*list;

	list = get_list_printf(0);
	if (!list->modif)
		return (ft_uitoabase(va_arg(ap, unsigned int), 10));
	else if (list->modif & 1)
		return (ft_uitoabase(va_arg(ap, unsigned long), 10));
	else if (list->modif & (1 << 1))
		return (ft_uitoabase(va_arg(ap, size_t), 10));
	else if (list->modif & (1 << 2))
		return (ft_uitoabase(va_arg(ap, unsigned int), 10));
	else if (list->modif & (1 << 3))
		return (ft_uitoabase((unsigned short)va_arg(ap, int), 10));
	else if (list->modif & (1 << 4))
		return (ft_uitoabase((unsigned char)va_arg(ap, int), 10));
	else if (list->modif & (1 << 5))
		return (ft_uitoabase(va_arg(ap, unsigned long long), 10));
	return (NULL);
}

char	*get_binary(va_list ap)
{
	t_printf	*list;

	list = get_list_printf(0);
	if (!list->modif)
		return (ft_uitoabase(va_arg(ap, unsigned int), 2));
	else if (list->modif & 1)
		return (ft_uitoabase(va_arg(ap, unsigned long), 2));
	else if (list->modif & (1 << 1))
		return (ft_uitoabase(va_arg(ap, size_t), 2));
	else if (list->modif & (1 << 2))
		return (ft_uitoabase(va_arg(ap, unsigned int), 2));
	else if (list->modif & (1 << 3))
		return (ft_uitoabase((unsigned short)va_arg(ap, int), 2));
	else if (list->modif & (1 << 4))
		return (ft_uitoabase((unsigned char)va_arg(ap, int), 2));
	else if (list->modif & (1 << 5))
		return (ft_uitoabase(va_arg(ap, unsigned long long), 2));
	return (NULL);
}
