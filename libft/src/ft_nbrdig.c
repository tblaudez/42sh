/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrdig.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 15:55:50 by tblaudez          #+#    #+#             */
/*   Updated: 2018/12/12 19:17:49 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nbrdig(int nbr, int base)
{
	int	i;

	if (base == 0)
		return (0);
	i = 1;
	while (nbr /= base)
		i++;
	return (i);
}