/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 15:04:07 by tblaudez          #+#    #+#             */
/*   Updated: 2018/10/12 13:23:41 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t i;

	if (!(*s2))
		return ((char*)s1);
	i = ft_strlen(s2);
	while (*s1 && len-- >= i)
	{
		if (*s1 == *s2 && !ft_memcmp(s1, s2, i))
			return ((char*)s1);
		s1++;
	}
	return (NULL);
}
