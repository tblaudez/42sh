/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 05:43:19 by tblaudez          #+#    #+#             */
/*   Updated: 2018/12/15 20:53:30 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		return_key(char buffer[6], t_shell *shell)
{
	char	c;

	(void)buffer;
	if (!check_line_live(shell))
		return (0);
	ft_putchar('\n');
	if (ft_strlen(shell->line->line_data + shell->line->prompt_len + 1))
		add_history_command(shell->line->line_data \
		+ shell->line->prompt_len + 1, shell, 0);
	if ((c = ft_quote(shell->line->line_data)))
	{
		if (!return_key_quote(shell, c))
			return (0);
		signal(SIGINT, &signal_handler);
	}
	return_final_line(shell);
	get_shell_struct(shell);
	tcsetattr(STDOUT_FILENO, TCSANOW, &shell->term_save);
	if (ft_strlen(shell->line->line_data))
		return_exec(shell);
	lt_release((void*)shell->line->line_data);
	shell->line->line_data = (char*)ft_memalloc(sizeof(char) * LINE_LEN);
	set_terminal(shell->term);
	display_prompt(shell);
	return (0);
}

int		del_key(char buffer[6], t_shell *shell)
{
	int		cpt;

	(void)buffer;
	if (shell->pos == shell->win.ws_col * (shell->cpt - 1))
	{
		shell->cpt--;
		tputs(tgetstr("up", NULL), 1, my_putchar);
		cpt = shell->win.ws_col;
		while (cpt-- > 0)
			tputs(tgetstr("nd", NULL), 1, my_putchar);
		tputs(tgetstr("dc", NULL), 1, my_putchar);
		shell->pos--;
		del_inline(shell);
		syncronize_line(shell);
		return (0);
	}
	if (shell->pos > shell->line->prompt_len + 1)
	{
		tputs(tgetstr("le", NULL), 1, my_putchar);
		tputs(tgetstr("dc", NULL), 1, my_putchar);
		shell->pos--;
		del_inline(shell);
		syncronize_line(shell);
	}
	return (0);
}

int		arrow_key(char buffer[6], t_shell *shell)
{
	if (buffer[1] == 91 && buffer[2] == 49 \
	&& buffer[3] == 59 && buffer[4] == 53 && buffer[5] == 65)
		keyup(shell);
	if (buffer[1] == 91 && buffer[2] == 49 \
	&& buffer[3] == 59 && buffer[4] == 53 && buffer[5] == 66)
		keydown(shell);
	if ((int)buffer[1] == 91 && buffer[2] == 72)
		keyhome(shell);
	if ((int)buffer[1] == 91 && (int)buffer[2] == 70)
		keyend(shell);
	if ((int)buffer[2] == 67 && (int)buffer[1] == 91)
		arrow_right(shell);
	if ((int)buffer[2] == 49 && (int)buffer[1] == 91 && buffer[5] == 67)
		arrow_right_ctrl(shell);
	if ((int)buffer[0] == 27 && (int)buffer[1] == 91 && buffer[5] == 68)
		arrow_left_ctrl(shell);
	if ((int)buffer[2] == 68 && (shell->pos > (shell->line->prompt_len + 1)))
		arrow_left(shell);
	if (buffer[2] == 65)
		history_up(shell);
	if (buffer[2] == 66)
		history_down(shell);
	return (0);
}

int		alpha_num(char buffer[6], t_shell *shell)
{
	char	*key;

	ft_putchar(buffer[0]);
	key = buffer;
	if (shell->pos < (int)ft_strlen(shell->line->line_data))
		alpha_inline(shell, buffer);
	else
		alpha_endline(shell, buffer);
	return (0);
}

void	init_key_func(t_shell *shell)
{
	int		i;

	i = 0;
	while (i < 128)
	{
		shell->key_function[i] = &other_key;
		if (i >= 32 && i <= 126)
			shell->key_function[i] = &alpha_num;
		i++;
	}
	shell->key_function[9] = &autocomplet;
	shell->key_function[12] = &clear_term;
	shell->key_function[16] = &start_yank;
	shell->key_function[21] = &start_past;
	shell->key_function[27] = &arrow_key;
	shell->key_function[4] = &ft_ctrl_d;
	shell->key_function[10] = &return_key;
	shell->key_function[127] = &del_key;
}
