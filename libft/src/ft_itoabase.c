/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoabase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 15:07:47 by tblaudez          #+#    #+#             */
/*   Updated: 2018/12/12 19:05:29 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoabase(int nbr, int base)
{
	char	*str;
	int		neg;
	int		i;

	if (base == 10)
		return (ft_itoa(nbr));
	neg = (nbr < 0 ? 1 : 0);
	nbr = (nbr < 0 ? -nbr : nbr);
	i = ft_nbrdig(nbr, base);
	if (!(str = ft_strnew(i)))
		return (NULL);
	while (i-- > 0)
	{
		str[i] = (nbr % base) + (nbr % base > 9 ? 'a' - 10 : '0');
		nbr /= base;
	}
	return (neg ? ft_strjoinfree("-", str, 0, 1) : str);
}
