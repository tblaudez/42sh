/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glob_match.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 19:08:14 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/15 20:53:30 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static char		*ft_make_patern(t_gdata *gdata)
{
	char	*patern;
	char	**split;
	int		i;
	int		j;

	i = 0;
	j = 0;
	split = ft_patern_split(gdata->case_str);
	patern = ft_strdup(split[i++]);
	while (split[i] || gdata->table[j])
	{
		if (gdata->table[j])
			patern = ft_strjoinfree(patern, gdata->table[j], 1, 0);
		if (split[i])
			patern = ft_strjoinfree(patern, split[i], 1, 0);
		i++;
		j++;
	}
	ft_tabdel(split);
	return (patern);
}

static int		ft_match_rec(int i, int index, char *element, t_gdata *gdata)
{
	char	*patern;

	while (gdata->case_tab[index][i])
	{
		lt_release((void*)gdata->table[index]);
		gdata->table[index] = ft_strdup(gdata->case_tab[index][i]);
		if (gdata->case_tab[index + 1])
		{
			if (ft_match_rec(0, index + 1, element, gdata))
				return (1);
		}
		else
		{
			patern = ft_make_patern(gdata);
			if (ft_check_patern(patern, element, 0, 0))
			{
				lt_release((void*)patern);
				return (1);
			}
			lt_release((void*)patern);
		}
		i++;
	}
	return (0);
}

static int		ft_try_match(char *element, t_gdata *gdata)
{
	if ((gdata->braces) && !gdata->brac_error)
		return (ft_match_rec(0, 0, element, gdata));
	else if (!gdata->brac_error)
		return (ft_check_patern(gdata->case_str, element, 0, 0));
	return (0);
}

static t_match	*ft_set_match(t_match *match, char *d_name, t_gdata *gdata)
{
	struct stat		path_stat;
	char			*path;

	path = (ft_strlen(gdata->path) == 0)
	? ft_strdup("./") : ft_strjoinfree(gdata->path, "/", 0, 0);
	path = ft_strjoinfree(path, d_name, 1, 0);
	if ((lstat(path, &path_stat)) == -1)
		ft_exit("21sh: lstat error");
	if (S_ISDIR(path_stat.st_mode))
		match = ft_match_add(d_name, match);
	else if (!S_ISDIR(path_stat.st_mode) && !(gdata->endslash))
		match = ft_match_add(d_name, match);
	lt_release((void*)path);
	return (match);
}

t_match			*ft_find_match(char **samples, t_gdata *gdata)
{
	struct dirent	*de;
	DIR				*dr;
	t_match			*match;

	match = 0;
	if (!(dr = opendir(gdata->path)))
	{
		if (ft_strlen(gdata->path) > 0)
			return (0);
		dr = opendir(".");
	}
	ft_case_tab(*samples, gdata);
	ft_case_str(*samples, gdata);
	gdata->table = (char **)(ft_memalloc(sizeof(char *)
	* (ft_nb_joker(gdata->case_str) + 1)));
	while ((de = readdir(dr)))
	{
		if ((de->d_name[0] != '.') && ft_try_match(de->d_name, gdata))
			match = ft_set_match(match, de->d_name, gdata);
	}
	closedir(dr);
	return (match);
}
