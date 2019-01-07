/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charsrc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 10:27:57 by tblaudez          #+#    #+#             */
/*   Updated: 2018/12/12 18:56:41 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_charsrc(const char *str, char c)
{
	int i;

	if (!str)
		return (-1);
	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i);
	return (-1);
}
