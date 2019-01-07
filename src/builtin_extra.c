/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_extra.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 13:47:37 by trponess          #+#    #+#             */
/*   Updated: 2018/12/15 20:53:30 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			create_process(char **args, char **ev)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		launch_binary(args, ev);
	if (pid)
		wait(&status);
}

static int		is_same_envvar(char *s1, char *s2)
{
	int i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i] && s1[i] != '=' && s2[i] != '=')
		i++;
	if ((s1[i] == '=' && !s2[i]) || (s1[i] == '=' && s2[i] == '='))
		return (1);
	return (0);
}

int				xlook_for_envvar(char **ev, char *var)
{
	int i;

	i = 0;
	if (!ev || !var)
		return (-1);
	while (ev[i])
	{
		if (is_same_envvar(ev[i], var))
			return (i);
		i++;
	}
	return (-1);
}

char			*search_for_command(char *command, char *env_path)
{
	char	buf[1000];
	int		i;
	int		j;

	if (access(command, X_OK) == 0 && !opendir(command))
		return (ft_strdup(command));
	i = 0;
	j = 0;
	while (env_path[i])
	{
		ft_bzero(&buf[0], 999);
		while (env_path[i] && env_path[i] != ':')
			buf[j++] = env_path[i++];
		buf[j] = '/';
		ft_strcat(buf, command);
		if (access(buf, X_OK) == 0 && !opendir(buf))
			return (ft_strdup(buf));
		j = 0;
		if (env_path[i] == ':')
			i++;
	}
	return (NULL);
}

void			ft_dmemdel(char ***arrptr)
{
	char	**arr;
	int		i;

	i = 0;
	arr = *arrptr;
	while (arr[i])
	{
		if (arr[i])
			lt_release((void*)arr[i]);
		i++;
	}
	lt_release((void*)arr);
	*arrptr = NULL;
}
