/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 15:03:49 by tblaudez          #+#    #+#             */
/*   Updated: 2018/10/12 13:23:38 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dst, const char *src, size_t len)
{
	int		i;
	size_t	j;

	i = ft_strlen(dst);
	j = -1;
	while (src[++j] && j < len)
		dst[i + j] = src[j];
	dst[i + j] = '\0';
	return (dst);
}
