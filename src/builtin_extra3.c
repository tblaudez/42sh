/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_extra3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 21:47:19 by trponess          #+#    #+#             */
/*   Updated: 2018/12/15 20:53:30 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	**add_pwdvar_to_env(char *pwd_var, char **ev)
{
	char	*tmp;
	char	*pwd_v;
	char	cwd[PATH_MAX + 1];

	pwd_v = ft_strdup(pwd_var);
	tmp = ft_strjoinfree(pwd_v, getcwd(cwd, PATH_MAX), 0, 0);
	pwd_v[ft_strlen(pwd_v)] = '\0';
	ev = add_to_env(xlook_for_envvar(ev, pwd_v), ev, tmp);
	lt_release((void*)pwd_v);
	lt_release((void*)tmp);
	return (ev);
}

char	**change_paths(char **paths, char **ev, char flag)
{
	int		i;
	char	tmp[PATH_MAX + 5];

	flag = 0;
	i = 0;
	while (paths[i])
	{
		if (ft_strequ("..", paths[i]))
		{
			getcwd(tmp, PATH_MAX);
			readlink(tmp, tmp, PATH_MAX);
			ft_strcat(tmp, "/..");
			if (chdir(tmp) == -1)
				ft_putendl_fd("cd: no such directory or access denied", 2);
			ev = add_pwdvar_to_env("PWD=", ev);
		}
		else
		{
			if (chdir(paths[i]) == -1)
				ft_putendl_fd("cd: no such directory or access denied", 2);
			ev = add_pwdvar_to_env("PWD=", ev);
		}
		i++;
	}
	return (ev);
}
