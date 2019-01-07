/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 15:01:59 by tblaudez          #+#    #+#             */
/*   Updated: 2018/12/15 20:53:30 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_history		*new_node(char *command, t_shell *shell)
{
	t_history	*maill;

	maill = ft_memalloc(sizeof(t_history));
	maill->command = ft_strdup(command);
	maill->next = NULL;
	maill->prev = NULL;
	shell->history = maill;
	return (maill);
}

void			add_history_command(char *command, t_shell *shell, int i)
{
	t_history	*temp;

	temp = NULL;
	if (!ft_strlen(command))
		return ;
	if (ft_str_is(&ft_isprint, command) == 1)
	{
		if (!shell->history)
		{
			shell->history = ft_memalloc(sizeof(t_history));
			shell->history->command = 0;
			shell->history->next = ft_memalloc(sizeof(t_history));
			shell->history->next->command = ft_strdup(command);
			shell->history->next->prev = shell->history;
			shell->history->old = i;
			shell->hist_ptr = shell->history;
		}
		else
			add_history_live(temp, shell, i, command);
	}
}

t_shell			*history_up(t_shell *shell)
{
	char	*tmp;

	if (!shell->history)
		return (shell);
	else if (shell->hist_ptr->next)
		shell->hist_ptr = shell->hist_ptr->next;
	if (shell->hist_ptr)
	{
		clear_line2(shell);
		display_prompt(shell);
		tmp = shell->line->line_data;
		ft_putstr(shell->hist_ptr->command);
		shell->line->line_data = ft_strjoinfree(shell->line->line_data,\
				shell->hist_ptr->command, 0, 0);
		lt_release((void*)tmp);
		while (shell->line->line_data[shell->pos])
			shell->pos++;
	}
	return (shell);
}

t_shell			*history_down(t_shell *shell)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!shell->history)
		return (shell);
	if (shell->hist_ptr && shell->hist_ptr->prev)
		shell->hist_ptr = shell->hist_ptr->prev;
	if (!shell->hist_ptr->command)
		return (history_down_clear(shell));
	if (shell->hist_ptr->command)
	{
		clear_line2(shell);
		display_prompt(shell);
		tmp = shell->line->line_data;
		ft_putstr(shell->hist_ptr->command);
		shell->line->line_data = \
		ft_strjoinfree(shell->line->line_data, shell->hist_ptr->command, 0, 0);
		lt_release((void*)tmp);
		while (shell->line->line_data[shell->pos])
			shell->pos++;
	}
	return (shell);
}
