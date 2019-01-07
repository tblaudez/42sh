/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_function_return.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 17:54:20 by mgazel            #+#    #+#             */
/*   Updated: 2018/12/15 21:38:55 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		return_key_quote(t_shell *shell, char c)
{
	signal(SIGINT, SIG_IGN);
	if (init_quote(c, shell) == 0)
	{
		ft_putchar('\n');
		lt_release((void*)shell->line->line_data);
		shell->line->line_data = (char*)ft_memalloc(sizeof(char) * LINE_LEN);
		display_prompt(shell);
		signal(SIGINT, &signal_handler);
		return (0);
	}
	return (1);
}

int		check_line_live(t_shell *shell)
{
	if (!ft_strlen(shell->line->line_data + shell->line->prompt_len + 1))
	{
		ft_putchar('\n');
		put_color(shell);
		return (0);
	}
	return (1);
}

void	catch_ctrl_c_onexec(int p)
{
	p = 1;
	ft_putchar('\n');
	get_shell_struct(NULL)->col = 1;
	return ;
}

void	return_exec(t_shell *shell)
{
	signal(SIGINT, &catch_ctrl_c_onexec);
	shell->token = create_token_list(shell->line->line_data);
	shell->cmd = create_cmd_list(shell->token);
	free_tk_list(shell->token);
	shell_exec(shell->cmd, shell->envp);
	free_cmd_list(shell->cmd);
	signal(SIGINT, &signal_handler);
}

void	return_final_line(t_shell *shell)
{
	char	*tmp;

	shell->col = 0;
	tmp = shell->line->line_data;
	shell->line->line_data = trimstartsp(shell->line->line_data,\
			shell->line->prompt_len + 1);
	lt_release((void*)tmp);
	tmp = shell->line->line_data;
	shell->line->line_data = ft_strdup(tmp + shell->line->prompt_len + 1);
	lt_release((void*)tmp);
	ft_glob_process(shell);
}
