/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 15:02:36 by tblaudez          #+#    #+#             */
/*   Updated: 2018/10/12 13:23:08 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*s1_dup;
	const unsigned char	*s2_dup;

	if (s1 == s2 || !n)
		return (0);
	s1_dup = (const unsigned char *)s1;
	s2_dup = (const unsigned char *)s2;
	while (n--)
	{
		if (*s1_dup != *s2_dup)
			return (*s1_dup - *s2_dup);
		if (n)
		{
			s1_dup++;
			s2_dup++;
		}
	}
	return (0);
}
