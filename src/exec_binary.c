/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 14:09:16 by tblaudez          #+#    #+#             */
/*   Updated: 2018/12/15 20:48:38 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int	test_rights(char *file)
{
	if (access(file, F_OK) == -1)
		return (0);
	if (access(file, X_OK) == -1)
	{
		ft_fprintf(2, "21sh: permission denied: %s\n", file);
		exit(EXIT_FAILURE);
	}
	return (1);
}

int			launch_binary(char **cmd, char **envp)
{
	char	**path;
	char	tmp[NAME_MAX + 1];
	int		i;

	signal(SIGINT, SIG_DFL);
	if (ft_strchr(cmd[0], '/') && test_rights(cmd[0]))
		execve(cmd[0], cmd, envp);
	path = ft_strsplit(get_env("PATH", envp), ':');
	i = -1;
	while (path && path[++i])
	{
		ft_strncpy(tmp, path[i], NAME_MAX);
		if (tmp[ft_strlen(tmp) - 1] != '/')
			ft_strlcat(tmp, "/", sizeof(tmp));
		ft_strlcat(tmp, cmd[0], sizeof(tmp));
		if (test_rights(tmp))
			execve(tmp, cmd, envp);
	}
	ft_strarraydel(&path);
	ft_fprintf(2, "21sh: %s: command not found\n", cmd[0]);
	exit(EXIT_FAILURE);
}
