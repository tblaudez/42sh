/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 17:29:15 by tblaudez          #+#    #+#             */
/*   Updated: 2018/12/12 18:58:11 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int nbr)
{
	char	*str;
	int		neg;
	int		i;

	neg = (nbr < 0 ? 1 : 0);
	nbr = ((nbr < 0) ? -nbr : nbr);
	i = ft_nbrdig(nbr, 10);
	if (!(str = ft_strnew(i)))
		return (NULL);
	while (i-- > 0)
	{
		str[i] = (nbr % 10) + '0';
		nbr /= 10;
	}
	return (neg ? ft_strjoinfree("-", str, 0, 1) : str);
}
