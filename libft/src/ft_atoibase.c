/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoibase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 14:25:48 by tblaudez          #+#    #+#             */
/*   Updated: 2018/12/12 19:30:33 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	convert(char c, int base)
{
	int ret;

	if (c >= '0' && c <= '9')
		ret = c - 48;
	else if (c >= 'a' && c <= 'z')
		ret = c - 97 + 10;
	else if (c >= 'A' && c <= 'Z')
		ret = c - 65 + 10;
	else
		ret = -1;
	if (ret < base && ret != -1)
		return (ret);
	else
		return (-1);
}

static int	nbr_digits(const char *str, int base)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (convert(str[i], base) < 0)
			break ;
		i++;
	}
	return (i);
}

int			ft_atoibase(const char *str, int base)
{
	int	ret;
	int	len;
	int	i;

	if (base == 10)
		return (ft_atoi(str));
	if (!str)
		return (0);
	while (ft_isspace(*str))
		str++;
	ret = 0;
	len = nbr_digits(str, base) - 1;
	i = 0;
	while (str[i] && len >= 0 && convert(str[i], base) >= 0)
	{
		ret += convert(str[i], base) * ft_power(base, len);
		len--;
		i++;
	}
	return (ret);
}
