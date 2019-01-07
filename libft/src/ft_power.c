/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 14:51:02 by tblaudez          #+#    #+#             */
/*   Updated: 2018/12/12 19:08:57 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_power(int nbr, int power)
{
	if (power == 0)
		return (1);
	else if (power < 0)
		return (0);
	else if (power > 0)
		nbr *= ft_power(nbr, --power);
	return (nbr);
}
