/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 23:49:56 by mgazel            #+#    #+#             */
/*   Updated: 2018/12/15 20:48:38 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		add_history_live(t_history *temp, t_shell *shell, int i,\
		char *command)
{
	temp = shell->history->next;
	shell->history->next = ft_memalloc(sizeof(t_history));
	shell->history->next->command = ft_strdup(command);
	temp->prev = shell->history->next;
	shell->history->next->next = temp;
	shell->history->next->prev = shell->history;
	shell->history->next->old = i;
	shell->hist_ptr = shell->history;
}

int			check_file(void)
{
	return (access("./.history", R_OK | W_OK));
}

t_shell		*read_file(t_shell *shell)
{
	int		fd;
	char	*tmp;

	fd = open("./.history", O_RDONLY);
	if (fd != -1)
	{
		while (get_next_line(fd, &tmp))
			add_history_command(tmp, shell, 1);
		close(fd);
	}
	return (shell);
}

void		make_history_file(t_shell *shell)
{
	int		fd;

	fd = open("./.history", O_WRONLY | O_CREAT);
	if (fd != -1)
	{
		while (shell->history->prev)
		{
			shell->history = shell->history->prev;
		}
		while (shell->history->next)
		{
			ft_putstr_fd(shell->history->command, fd);
			ft_putstr_fd("\n", fd);
			shell->history = shell->history->next;
		}
		ft_putstr_fd(shell->history->command, fd);
		ft_putstr_fd("\n", fd);
		close(fd);
	}
}

void		setup_history(t_shell **shell)
{
	if (check_file() == 0)
		*shell = read_file(*shell);
}
