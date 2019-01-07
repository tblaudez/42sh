/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 09:47:28 by tblaudez          #+#    #+#             */
/*   Updated: 2018/08/09 21:39:20 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(const int fd, char **line)
{
	static char	*tmp = NULL;
	char		buf[BUFF_SIZE + 1];
	int			i;

	if (fd < 0)
		return (-1);
	i = 1;
	while (!ft_strchr(tmp, '\n') && i > 0)
	{
		i = read(fd, buf, BUFF_SIZE);
		buf[i] = '\0';
		tmp = ft_strjoinfree(tmp, ft_strdup(buf), 1, 1);
	}
	if (i <= 0 && ft_strequ(tmp, ""))
		return (i);
	i = ft_charsrc(tmp, '\n');
	(*line) = (i >= 0 ? ft_strsub(tmp, 0, i) : tmp);
	tmp = (i >= 0 ? ft_strcpy(tmp, tmp + i + 1) : NULL);
	return (1);
}
