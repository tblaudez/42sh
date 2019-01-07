/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glob_recreate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 19:42:10 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/15 20:53:30 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			ft_new_line_data(char *word, t_gdata *gdata)
{
	t_match	*start;
	char	*prefix;
	char	*rest;
	char	*ptr;
	int		i;

	i = 0;
	ptr = gdata->new_line;
	while (ft_strncmp(word, ptr++, ft_strlen(word)))
		i++;
	prefix = (i > 0) ? ft_strsub(gdata->new_line, 0, i) : ft_strdup("");
	rest = ft_strdup(gdata->new_line + i + ft_strlen(word));
	lt_release((void*)gdata->new_line);
	gdata->new_line = ft_strdup(prefix);
	lt_release((void*)prefix);
	start = gdata->glob_lst;
	while (gdata->glob_lst)
	{
		gdata->new_line = ft_strjoinfree(gdata->new_line,
				gdata->glob_lst->name, 1, 0);
		gdata->new_line = ft_strjoinfree(gdata->new_line, " ", 1, 0);
		gdata->glob_lst = gdata->glob_lst->next;
	}
	gdata->glob_lst = start;
	gdata->new_line = ft_strjoinfree(gdata->new_line, rest, 1, 1);
}
