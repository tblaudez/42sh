/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_catchsign.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 15:01:52 by tblaudez          #+#    #+#             */
/*   Updated: 2018/12/15 20:53:30 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void		signal_winch(void)
{
	t_shell		*shell;
	int			i;
	int			j;

	shell = get_shell_struct(NULL);
	i = shell->pos;
	j = i;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &shell->win);
	shell->cpt = ((ft_strlen(shell->line->line_data) / shell->win.ws_col) + 1);
	keyhome(shell);
	while (i-- > 0)
		tputs(tgetstr("le", NULL), 0, my_putchar);
	tputs(tgetstr("cd", NULL), 0, my_putchar);
	put_color(shell);
	shell->pos = ft_strlen(shell->line->line_data);
	keyhome(shell);
	keyend(shell);
}

void			signal_handler2(int signo)
{
	t_shell			*shell;
	struct termios	term;

	tcgetattr(STDOUT_FILENO, &term);
	shell = get_shell_struct(NULL);
	if (signo == SIGCONT)
	{
		init_term(&term);
		tcsetattr(STDOUT_FILENO, TCSANOW, &term);
		put_color(shell);
		signal(SIGTSTP, signal_handler);
	}
	else if (signo == SIGWINCH)
		signal_winch();
	else if (signo == SIGHUP || signo == SIGXCPU || signo == SIGXFSZ \
	|| signo == SIGVTALRM || signo == SIGPROF)
		ft_exit("21sh: signal received");
}

void			signal_handler(int signo)
{
	struct termios	term;
	char			tmp[2];

	tcgetattr(STDOUT_FILENO, &term);
	if (signo == SIGTSTP)
	{
		tmp[0] = term.c_cc[VSUSP];
		tmp[1] = '\0';
		signal(SIGTSTP, SIG_DFL);
		ioctl(STDOUT_FILENO, TIOCSTI, tmp);
	}
	else if (signo == SIGINT || signo == SIGQUIT)
	{
		if (get_shell_struct(NULL)->line->line_data[0] != 'p' \
		&& get_shell_struct(NULL)->line->line_data[0] != 'h')
		{
			keyend(get_shell_struct(NULL));
			lt_release((void*)get_shell_struct(NULL)->line->line_data);
			get_shell_struct(NULL)->line->line_data = \
					(char*)ft_memalloc(sizeof(char) * LINE_LEN);
			ft_putchar('\n');
			get_shell_struct(NULL)->col = 1;
			display_prompt(get_shell_struct(NULL));
		}
	}
}

t_shell			*get_shell_struct(t_shell *shell)
{
	static t_shell *save;

	if (shell != NULL)
		save = shell;
	return (save);
}

void			ft_catchsign(void)
{
	signal(SIGTSTP, &signal_handler);
	signal(SIGINT, &signal_handler);
	signal(SIGQUIT, &signal_handler);
	signal(SIGCONT, &signal_handler2);
	signal(SIGWINCH, &signal_handler2);
	signal(SIGHUP, &signal_handler2);
	signal(SIGXCPU, &signal_handler2);
	signal(SIGXFSZ, &signal_handler2);
	signal(SIGVTALRM, &signal_handler2);
	signal(SIGPROF, &signal_handler2);
	signal(SIGTERM, &signal_handler2);
}
