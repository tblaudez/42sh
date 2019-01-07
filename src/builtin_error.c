/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 13:47:17 by trponess          #+#    #+#             */
/*   Updated: 2018/12/15 20:53:30 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int		ft_error_two(char **line, int **flag)
{
	int i;

	**flag = 0;
	if (ft_strequ(line[0], "env") && ft_strequ(line[1], "-i"))
		**flag = 1;
	i = **flag + 1;
	while (line[i] && ft_strstr(line[i], "=") && line[i][0] != '=')
		i++;
	if (line[i] && ft_strequ(line[0], "setenv"))
	{
		ft_fprintf(STDERR_FILENO, "invalid option : %s\n", line[i]);
		return (-1);
	}
	return (i);
}

int				ft_error(char **line, int *flag, char **ev)
{
	int		i;
	int		pos;
	char	*tmp;

	tmp = NULL;
	if ((i = ft_error_two(line, &flag)) == -1)
		return (0);
	if (line[i] && ft_strequ(line[0], "env"))
	{
		pos = xlook_for_envvar(ev, "PATH");
		if (pos > -1 && (tmp = search_for_command(line[i], &ev[pos][5])))
			;
		if (pos == -1 || !tmp)
		{
			ft_fprintf(2, "not an executable : %s\n", line[i]);
			return (0);
		}
	}
	return (1);
}

static char		**reput_slash(char **line, int i)
{
	char	**tmp;

	if (line[i][0] == '/')
	{
		tmp = ft_strsplit(line[i], '/');
		tmp[0] = ft_strjoinfree("/", tmp[0], 0, 0);
		return (tmp);
	}
	else
		return (ft_strsplit(line[i], '/'));
}

char			**cd_flag(char **ev, char **line, char *flag_l)
{
	int i;

	i = 1;
	*flag_l = 'L';
	while (((ft_strequ(line[i], "-P") || ft_strequ(line[i], "-L")))\
		&& line[i++])
		(ft_strequ(line[i], "-P")) ? *flag_l = 'P' : 'L';
	if (ft_strequ(line[i], "-") && get_env("OLDPWD", ev))
	{
		lt_release((void*)line[i]);
		line[i] = ft_strdup(get_env("OLDPWD", ev));
		ft_fprintf(1, "%s\n", line[i]);
		return (ft_strsplit(line[i], ' '));
	}
	if (ft_strequ("/", line[i]))
	{
		lt_release((void*)line[i]);
		line[i] = ft_strdup("/");
		return (ft_strsplit(line[i], ' '));
	}
	if (line[i])
		return (reput_slash(line, i));
	return (NULL);
}
