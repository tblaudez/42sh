/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 15:03:01 by tblaudez          #+#    #+#             */
/*   Updated: 2018/10/12 13:23:25 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dst, const char *src)
{
	int i;
	int j;

	if (!src)
		return (dst);
	i = ft_strlen(dst);
	j = -1;
	while (src[++j])
		dst[i + j] = src[j];
	dst[i + j] = '\0';
	return (dst);
}
