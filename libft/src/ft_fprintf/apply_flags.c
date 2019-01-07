/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 16:35:26 by tblaudez          #+#    #+#             */
/*   Updated: 2018/10/11 15:18:11 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

char	*apply_hash(char *str, char conv)
{
	t_printf	*list;

	if (*str == '0' || ft_strchr("cdisu", conv))
		return (str);
	list = get_list_printf(0);
	if (conv == 'x')
		str = ft_strjoinfree("0x", str, 0, 1);
	else if (conv == 'X')
		str = ft_strjoinfree("0X", str, 0, 1);
	else if (conv == 'o')
		list->preci = ft_strlen(str) + 1;
	list->width -= 2;
	return (str);
}

char	*apply_zero(char *str, char conv)
{
	t_printf	*list;
	int			i;
	char		*tmp;

	list = get_list_printf(0);
	if ((list->preci != -1 && ft_strchr("diouxX", conv)) \
		|| list->width <= ft_strlen(str) || ft_strchr("sScCp", conv))
		return (str);
	i = list->width - ft_strlen(str);
	tmp = ft_strnew(i);
	ft_memset(tmp, '0', i);
	str = ft_strjoinfree(tmp, str, 1, 1);
	if (conv == 'd' && ft_strchr(str, '-'))
	{
		str = ft_strreplace(str, '-', '0');
		str[0] = '-';
	}
	return (str);
}

char	*apply_minus(char *str)
{
	int			i;
	t_printf	*list;
	char		*tmp;

	list = get_list_printf(0);
	if (list->width <= ft_strlen(str))
		return (str);
	i = list->width - ft_strlen(str);
	tmp = ft_strnew(i);
	ft_memset(tmp, ' ', i);
	return (ft_strjoinfree(str, tmp, 1, 1));
}

char	*apply_space(char *str, char conv)
{
	if (!ft_strchr("id", conv) || *str == '-')
		return (str);
	return (ft_strjoinfree(" ", str, 0, 1));
}

char	*apply_plus(char *str, char conv)
{
	if (!ft_strchr("id", conv) || *str == '-')
		return (str);
	return (ft_strjoinfree("+", str, 0, 1));
}
