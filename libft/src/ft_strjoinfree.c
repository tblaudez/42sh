/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 14:47:55 by tblaudez          #+#    #+#             */
/*   Updated: 2018/12/15 20:53:30 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinfree(char *s1, char *s2,
int free1, int free2)
{
	char *str;

	if (!s1 || !s2)
		return (!s2 ? s1 : s2);
	str = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	str = ft_strcpy(str, s1);
	str = ft_strcat(str, s2);
	if (s1 == s2 && (free1 == 1 || free2 == 1))
	{
		lt_release((void*)s1);
		return (str);
	}
	if (free1 == 1)
		lt_release((void*)s1);
	if (free2 == 1)
		lt_release((void*)s2);
	return (str);
}
