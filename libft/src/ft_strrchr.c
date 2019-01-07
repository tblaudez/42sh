/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 15:04:12 by tblaudez          #+#    #+#             */
/*   Updated: 2018/10/12 13:23:41 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp;
	int		i;

	if (!(char)c)
		return ((char*)s + ft_strlen(s));
	tmp = (char*)s;
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			tmp = (char*)s + i;
		i++;
	}
	return (tmp);
}
