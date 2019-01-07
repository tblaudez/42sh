/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 14:05:21 by tblaudez          #+#    #+#             */
/*   Updated: 2018/12/15 21:12:45 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	**create_env(char **envp)
{
	char	**tmp;
	int		i;

	i = -1;
	while (envp[++i])
		continue ;
	tmp = (char**)ft_memalloc(sizeof(char*) * i * 2);
	i = -1;
	while (envp[++i])
	{
		if (ft_strnequ("SHLVL=", envp[i], 6))
			tmp[i] = ft_strjoinfree("SHLVL=", \
			ft_itoa(ft_atoi(ft_strrchr(envp[i], '=') + 1) + 1), 0, 1);
		else
			tmp[i] = ft_strdup(envp[i]);
	}
	return (tmp);
}

char	*get_env(char *name, char **envp)
{
	int	i;
	int	j;

	while (*envp)
	{
		i = ft_charsrc(*envp, '=');
		j = ft_strlen(name);
		if (ft_strnequ(*envp, name, i) && ft_strnequ(name, *envp, j))
			return (*envp + i + 1);
		envp++;
	}
	return (NULL);
}

void	free_tk_list(t_token *tk_list)
{
	t_token	*tmp;

	while (tk_list)
	{
		tmp = tk_list;
		tk_list = tk_list->next;
		ft_strdel(&tmp->lexeme);
		lt_release((void*)tmp);
	}
}

void	free_cmd_list(t_cmd *cmd_list)
{
	t_cmd	*tmp;
	t_redir	*tmp2;
	int		i;

	while (cmd_list)
	{
		i = 0;
		tmp = cmd_list;
		cmd_list = cmd_list->next;
		while (tmp->args && tmp->args[i])
			ft_strdel(&tmp->args[i++]);
		while (tmp->redir)
		{
			tmp2 = tmp->redir;
			tmp->redir = tmp->redir->next;
			lt_release((void*)tmp2);
		}
		lt_release((void*)tmp);
	}
}

int		check_syntax_error(t_token *tk_list)
{
	if (tk_list && (tk_list->type == D_AND \
	|| tk_list->type == D_PIPE))
		return (0);
	while (tk_list)
	{
		if (tk_list->type == S_ERROR)
			return (0);
		if (tk_list->type == EOL)
			return (1);
		if ((ft_is_type("redir", tk_list->type) || tk_list->type == PIPE) \
		&& (!tk_list->next || tk_list->next->type == EOL))
			return (0);
		if (ft_is_type("separator", tk_list->type) \
		&& ft_is_type("separator", tk_list->next->type))
			return (0);
		tk_list = tk_list->next;
	}
	return (1);
}
