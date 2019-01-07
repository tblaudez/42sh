/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhome.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 20:42:01 by tblaudez          #+#    #+#             */
/*   Updated: 2018/12/15 20:48:38 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	keyhome(t_shell *shell)
{
	int		cpt;

	while (shell->pos > shell->line->prompt_len + 1)
	{
		if (shell->pos == shell->win.ws_col * (shell->cpt - 1))
		{
			shell->cpt--;
			tputs(tgetstr("up", NULL), 1, my_putchar);
			cpt = shell->win.ws_col;
			while (cpt-- > 0)
				tputs(tgetstr("nd", NULL), 1, my_putchar);
			shell->pos--;
		}
		else
		{
			tputs(tgetstr("le", NULL), 1, my_putchar);
			shell->pos--;
		}
	}
}

void	keyend(t_shell *shell)
{
	while (shell->line->line_data[shell->pos])
	{
		if (shell->pos + 1 == shell->win.ws_col * shell->cpt)
		{
			tputs(tgetstr("do", NULL), 1, my_putchar);
			shell->cpt++;
			shell->pos++;
		}
		else
		{
			shell->pos++;
			tputs(tgetstr("nd", NULL), 1, my_putchar);
		}
	}
}

void	keyup(t_shell *shell)
{
	int		i;

	i = 0;
	if (shell->cpt > 1)
	{
		tputs(tgetstr("up", NULL), 1, my_putchar);
		shell->pos = shell->pos - shell->win.ws_col;
		if (shell->pos < shell->line->prompt_len + 1)
			while (i++ < shell->line->prompt_len + 1)
			{
				tputs(tgetstr("nd", NULL), 1, my_putchar);
				shell->pos++;
			}
	}
}

void	keydown(t_shell *shell)
{
	int		i;

	i = 0;
	if (shell->cpt < ft_strlen(shell->line->line_data) / shell->win.ws_col + 1)
	{
		tputs(tgetstr("do", NULL), 1, my_putchar);
		i = shell->pos % shell->win.ws_col;
		shell->pos = shell->pos + shell->win.ws_col;
		while (--i)
			tputs(tgetstr("nd", NULL), 1, my_putchar);
		while (--shell->pos > ft_strlen(shell->line->line_data))
			tputs(tgetstr("le", NULL), 1, my_putchar);
	}
}
