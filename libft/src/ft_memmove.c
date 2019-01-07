/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 15:02:49 by tblaudez          #+#    #+#             */
/*   Updated: 2018/12/05 17:51:49 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dst_dup;
	char	*src_dup;
	int		i;

	dst_dup = (char*)dst;
	src_dup = (char*)src;
	i = 0;
	if (dst_dup > src_dup)
		while ((int)(--len) >= 0)
			*(dst_dup + len) = *(src_dup + len);
	else
		while (i < (int)len)
		{
			*(dst_dup + i) = *(src_dup + i);
			i++;
		}
	return (dst_dup);
}
