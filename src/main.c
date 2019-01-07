/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 11:40:59 by tblaudez          #+#    #+#             */
/*   Updated: 2018/12/15 20:48:38 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int				ft_ctrl_d(char buffer[6], t_shell *shell)
{
	(void)buffer;
	if (!ft_strlen(shell->line->line_data + shell->pos) && \
	ft_strlen(shell->line->line_data + shell->line->prompt_len + 1))
		return (0);
	else if (ft_strlen(shell->line->line_data + shell->pos))
	{
		shell->pos++;
		tputs(tgetstr("nd", NULL), 1, my_putchar);
		del_key(buffer, shell);
		return (0);
	}
	else if (shell->line->line_data[0] == 'p')
	{
		ft_putstr_fd("21sh: Unexpected EOF", 2);
		return (0);
	}
	else if (shell->line->line_data[0] == 'h')
		return (1);
	else
		ft_exit("exit");
	return (0);
}

void			set_terminal(struct termios term)
{
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(2, TCSANOW, &term) == -1)
		ft_exit("21sh: Unable to initiate terminal.");
}

void			init_terminal(t_shell *shell)
{
	char	*termtype;

	if (!(termtype = getenv("TERM")))
		ft_exit("21sh: TERM variable is not set");
	if (tgetent(NULL, termtype) <= 0)
		ft_exit("21sh: terminal not recognized");
	if (tcgetattr(STDOUT_FILENO, &shell->term) == -1)
		ft_exit("21sh: tcgetattr error");
	shell->term_save = shell->term;
	set_terminal(shell->term);
}

t_shell			*init_shell(char **envp)
{
	t_shell	*shell;

	shell = (t_shell*)ft_memalloc(sizeof(t_shell));
	shell->line = (t_line*)ft_memalloc(sizeof(t_line));
	shell->line->line_data = (char*)ft_memalloc(sizeof(char) * LINE_LEN);
	setup_history(&shell);
	init_terminal(shell);
	shell->envp = create_env(envp);
	shell->col = 0;
	return (shell);
}

int				main(int ac, char **av, char **envp)
{
	t_shell	*shell;

	(void)av;
	(void)ac;
	ft_catchsign();
	shell = init_shell(envp);
	while (shell->history && shell->history->next)
		shell->history = shell->history->next;
	get_shell_struct(shell);
	key_reader(shell);
	return (0);
}
