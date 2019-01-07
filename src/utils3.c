/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 17:13:11 by tblaudez          #+#    #+#             */
/*   Updated: 2018/12/15 21:34:16 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char		ft_end_check(char *str)
{
	int		ok;
	int		i;

	ok = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] != ' ')
			ok = 0;
		if ((str[i] == '&' && str[i + 1] == '&')
		|| (str[i] == '|' && str[i + 1] == '|'))
		{
			ok = 1;
			i++;
		}
		else if (str[i] == '\\')
		{
			get_shell_struct(NULL)->line->line_data[ft_strlen(\
			get_shell_struct(NULL)->line->line_data) - 1] = '\0';
			ok = 1;
		}
		else if (str[i] == '\n')
			ok = 1;
	}
	return ((ok == 1) ? '\n' : 0);
}

char		ft_quote(char *str)
{
	int			quot;
	int			dquot;
	int			i;

	i = 0;
	quot = 0;
	dquot = 0;
	while (str[i])
	{
		if (str[i] == '\\' && (str[i + 1] == '\'' || str[i + 1] == '\"'))
		{
			i = (str[i + 1]) ? i + 2 : i + 1;
			continue ;
		}
		if (str[i] == '\'' && !dquot)
			quot = (quot) ? 0 : 1;
		else if (str[i] == '\"' && !quot)
			dquot = (dquot) ? 0 : 1;
		i++;
	}
	if (!quot && !dquot)
		return (ft_end_check(str));
	return ((quot) ? '\'' : '\"');
}

int			look_for_quotes(t_token *tk_list, char *input)
{
	int	len;

	tk_list->type = input[0];
	len = 1;
	while (input[len] && input[len] != input[0])
		len++;
	if (len - 1 == 0)
	{
		tk_list->lexeme = ft_strdup(" ");
		return (2);
	}
	tk_list->lexeme = ft_strsub(input, 1, len - 1);
	return (len + 1);
}

void		close_all(t_redir *redir_list)
{
	while (redir_list)
	{
		if (ft_str_is(&ft_isdigit, redir_list->to))
			if (isatty(ft_atoi(redir_list->to)))
				close(ft_atoi(redir_list->to));
		redir_list = redir_list->next;
	}
}

t_cmd		*check_success(pid_t pid, t_cmd *cmd_list)
{
	t_shell	*shell;

	shell = get_shell_struct(NULL);
	if (WIFEXITED(pid) && !WEXITSTATUS(pid))
	{
		shell->col = 0;
		while (ft_is_in("dpipe", cmd_list))
			cmd_list = cmd_list->next;
	}
	else if ((WIFEXITED(pid) && WEXITSTATUS(pid)) || (WIFSIGNALED(pid) \
	&& (WTERMSIG(pid) == SIGINT || WTERMSIG(pid) == SIGQUIT)))
		while (ft_is_in("dand", cmd_list))
			cmd_list = cmd_list->next;
	return (cmd_list->next);
}
