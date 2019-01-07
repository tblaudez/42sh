/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 14:16:14 by tblaudez          #+#    #+#             */
/*   Updated: 2018/12/15 20:48:38 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int			print_pwd(t_shell *shell)
{
	char	pwd[100];
	char	*tmp;

	if (getcwd(pwd, 100) == NULL)
		return (0);
	tmp = ft_strrchr(pwd, '/') + 1;
	if (!tmp || !ft_strlen(tmp))
		tmp = ft_strdup("/");
	put_line(tmp, shell);
	return (ft_strlen(tmp));
}

void		display_prompt(t_shell *shell)
{
	shell->pos = 0;
	put_line("[", shell);
	shell->line->prompt_len = print_pwd(shell) + 5;
	put_line("]", shell);
	put_line(" $> ", shell);
	if (shell->col == 0)
		ft_fprintf(1, "{green}%s{eoc}", shell->line->line_data);
	else
		ft_fprintf(1, "{red}%s{eoc}", shell->line->line_data);
}

char		**obj_envp(char **new_envp)
{
	static char **envp;

	if (new_envp)
		envp = ft_dup_env(new_envp);
	return (envp);
}

int			key_reader(t_shell *shell)
{
	char	buffer[6];
	int		tmp;

	tmp = 0;
	init_key_func(shell);
	display_prompt(shell);
	obj_envp(shell->envp);
	while (1)
	{
		shell->envp = obj_envp(NULL);
		ft_memset(buffer, '\0', 6);
		ioctl(2, TIOCGWINSZ, &shell->win);
		shell->cpt = (shell->pos / shell->win.ws_col) + 1;
		read(0, buffer, 6);
		if ((int)buffer[0] < 0)
			tmp++;
		else
		{
			if (((shell->key_function)[(int)buffer[0]])(buffer, shell))
				return (1);
		}
	}
	return (0);
}
