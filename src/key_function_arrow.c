/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_function_arrow.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 18:39:46 by mgazel            #+#    #+#             */
/*   Updated: 2018/12/15 20:48:38 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	arrow_right(t_shell *shell)
{
	if (shell->pos < (shell->win.ws_col * shell->cpt))
	{
		if (shell->pos < (int)ft_strlen(shell->line->line_data))
		{
			tputs(tgetstr("nd", NULL), 1, my_putchar);
			shell->pos++;
		}
	}
	if (shell->pos == (shell->win.ws_col * shell->cpt))
	{
		if (shell->pos <= (int)ft_strlen(shell->line->line_data))
		{
			tputs(tgetstr("do", NULL), 1, my_putchar);
			shell->cpt++;
		}
	}
}

void	arrow_right_ctrl(t_shell *shell)
{
	int		etr;

	etr = 1;
	while (shell->line->line_data[shell->pos] && \
	(shell->line->line_data[shell->pos - 1] != ' ' || \
	shell->line->line_data[shell->pos] == ' ' || etr == 1))
	{
		if (shell->pos == (shell->win.ws_col * shell->cpt))
		{
			tputs(tgetstr("do", NULL), 1, my_putchar);
			shell->cpt++;
		}
		shell->pos++;
		etr = 2;
		tputs(tgetstr("nd", NULL), 1, my_putchar);
		if (shell->pos == (shell->win.ws_col * shell->cpt))
		{
			tputs(tgetstr("do", NULL), 1, my_putchar);
			shell->cpt++;
		}
	}
}

void	arrow_left_ctrl(t_shell *shell)
{
	int		etr;

	etr = 1;
	while ((shell->pos > shell->line->prompt_len + 1) && \
	(shell->line->line_data[shell->pos - 1] != ' ' || etr == 1))
	{
		arrow_left(shell);
		etr = 2;
		while (shell->line->line_data[shell->pos] == ' ' &&\
				shell->pos > shell->line->prompt_len + 1)
			arrow_left(shell);
	}
}

void	arrow_left(t_shell *shell)
{
	int		cpt;

	if ((shell->pos) == (shell->win.ws_col * (shell->cpt - 1)))
	{
		shell->cpt--;
		tputs(tgetstr("up", NULL), 1, my_putchar);
		cpt = shell->win.ws_col;
		while (cpt-- > 0)
			tputs(tgetstr("nd", NULL), 1, my_putchar);
	}
	else
		tputs(tgetstr("le", NULL), 1, my_putchar);
	shell->pos--;
}
