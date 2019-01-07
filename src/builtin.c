/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 18:38:51 by trponess          #+#    #+#             */
/*   Updated: 2018/12/15 20:48:38 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void		check_special_char(char *line)
{
	const char	tab1[9] = {'a', 'b', 'f', 'r', 'n', 't', 'v', '\\', '\0'};
	const char	t2[9] = {'\a', '\b', '\f', '\r', '\n', '\t', '\v', '\\', '\0'};
	int			i;
	int			j;

	j = 0;
	while (line[j])
	{
		if (line[j] == '\\' && (i = ft_charsrc(tab1, line[j + 1])) >= 0)
		{
			line[j] = t2[i];
			ft_strcpy(line + j + 1, line + j + 2);
		}
		j++;
	}
}

void			ft_echo(char **line)
{
	int	flag;
	int	i;

	i = 0;
	flag = (ft_strequ(line[1], "-n") ? 1 : 0);
	i = (flag == 1 ? 2 : 1);
	while (line[i])
	{
		check_special_char(line[i]);
		write(1, line[i], ft_strlen(line[i]));
		if (line[i + 1])
			ft_putchar(' ');
		i++;
	}
	if (!flag)
		ft_putchar('\n');
	else
		ft_fprintf(1, "{reverse}%c\n{eoc}", '%');
}

char			**ft_cd(char **ev, char **line)
{
	char	flag_l;
	char	**paths;
	char	*env_var;

	if (!line)
		return (ev);
	if (!line[1] && (env_var = get_env("HOME", ev)))
	{
		if (chdir(env_var) == -1)
			ft_putendl_fd("21sh: cd: no such directory or access denied", 2);
		ev = add_pwdvar_to_env("PWD=", ev);
		return (ev);
	}
	else if (!line[1])
	{
		ft_putendl_fd("21sh: envvar HOME doesn't exist", 2);
		return (ev);
	}
	paths = cd_flag(ev, line, &flag_l);
	if (!paths)
		return (NULL);
	ev = add_pwdvar_to_env("OLDPWD=", ev);
	ev = change_paths(paths, ev, flag_l);
	ft_dmemdel(&paths);
	return (ev);
}

void			ft_env(char **line, char **ev)
{
	int		flag;
	char	**cpy_ev;

	if (!ev || !line || !ft_error(line, &flag, ev))
		return ;
	if (!flag++)
		cpy_ev = ft_dup_env(ev);
	else
	{
		if (!(cpy_ev = (char **)ft_memalloc(sizeof(char *) * 1)))
			return ;
		cpy_ev[0] = 0;
	}
	while (line[flag] && access(line[flag], X_OK) == -1 \
		&& ft_strstr(line[flag], "="))
	{
		cpy_ev = add_to_env(xlook_for_envvar(cpy_ev, line[flag]) \
		, cpy_ev, line[flag]);
		flag++;
	}
	(!line[flag]) ? display_env(cpy_ev) \
	: create_process(&line[flag], cpy_ev);
	(cpy_ev) ? ft_dmemdel(&cpy_ev) : 0;
}

char			**ft_set_un_env(char **line, char **ev)
{
	int		flag;
	char	**cpy_ev;
	int		pos;

	if (!ev || !line || !ft_error(line, &flag, ev))
		return (ev);
	cpy_ev = ft_dup_env(ev);
	flag = 1;
	while (line[flag])
	{
		pos = xlook_for_envvar(cpy_ev, line[flag]);
		if (ft_strequ(line[0], "setenv"))
			cpy_ev = add_to_env(pos, cpy_ev, line[flag]);
		if (ft_strequ(line[0], "unsetenv"))
			cpy_ev = remove_from_env(pos, cpy_ev);
		flag++;
	}
	return (cpy_ev);
}
