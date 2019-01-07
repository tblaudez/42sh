/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 15:12:49 by tblaudez          #+#    #+#             */
/*   Updated: 2018/10/15 17:04:10 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Replace a char by another in a string
**	ACHTUNG: the string memory must be editable.
*/

char	*ft_strreplace(char *str, char c1, char c2)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c1)
			str[i] = c2;
		i++;
	}
	return (str);
}
