/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glob_recloop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 19:44:25 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/15 20:53:30 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void		ft_check_brac(char **samples, int i, t_gdata *gdata)
{
	gdata->brackets = ft_glob_brackets(samples[i]);
	gdata->braces = ft_glob_braces(samples[i]);
	gdata->brac_error =
	(gdata->brackets == -1 || gdata->braces == -1) ? 1 : 0;
}

static void		ft_match_try(char **samples, t_match *match, t_gdata *gdata)
{
	char	*temp_path;

	temp_path = ft_strdup(gdata->path);
	if (!ft_strequ(gdata->path, "") && !ft_strequ(gdata->path, "/"))
		gdata->path = ft_strjoinfree(gdata->path, "/", 1, 0);
	gdata->path = ft_strjoinfree(gdata->path, match->name, 1, 0);
	ft_glob_rec(samples + 1, gdata);
	lt_release((void*)gdata->path);
	gdata->path = ft_strdup(temp_path);
	lt_release((void*)temp_path);
}

void			ft_glob_rec(char **samples, t_gdata *gdata)
{
	t_match *match;
	t_match	*start;
	int		i;

	i = 0;
	if (!samples[i])
	{
		gdata->glob_lst = ft_match_add(gdata->path, gdata->glob_lst);
		return ;
	}
	match = 0;
	ft_check_brac(samples, i, gdata);
	match = ft_find_match(samples + i, gdata);
	start = match;
	while (match)
	{
		ft_match_try(samples, match, gdata);
		match = match->next;
	}
	match = start;
	ft_free_lst(match);
}

void			ft_glob_loop(char **samples, t_gdata *gdata)
{
	int			i;

	i = 0;
	ft_check_brac(samples, i, gdata);
	if (gdata->startslash)
		gdata->path = ft_strjoinfree(gdata->path, "/", 1, 0);
	if (!ft_strchr(samples[0], '*') && !ft_strchr(samples[0], '?')
	&& ((!gdata->brackets && !gdata->braces) || gdata->brac_error))
	{
		gdata->path = ft_strjoinfree(gdata->path, samples[0], 1, 0);
		if (samples[++i])
			ft_check_brac(samples, i, gdata);
		while (samples[i]
		&& !ft_strchr(samples[i], '*') && !ft_strchr(samples[i], '?')
		&& ((!gdata->brackets && !gdata->braces) || gdata->brac_error))
		{
			gdata->path = ft_strjoinfree(gdata->path, "/", 1, 0);
			gdata->path = ft_strjoinfree(gdata->path, samples[i], 1, 0);
			if (samples[++i])
				ft_check_brac(samples, i, gdata);
		}
	}
	ft_glob_rec(samples + i, gdata);
}
