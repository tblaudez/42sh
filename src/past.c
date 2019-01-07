/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   past.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 21:10:28 by mgazel            #+#    #+#             */
/*   Updated: 2018/12/15 20:53:30 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void		init_past(t_shell *shell, int *tmpp, char buffer[6])
{
	int			cpt;

	(void)buffer;
	*tmpp = shell->pos;
	keyhome(shell);
	cpt = ((ft_strlen(shell->line->line_data) + \
	ft_strlen(shell->yank)) / shell->win.ws_col) + 2;
	while (cpt--)
		ft_putchar('\n');
	cpt = ((ft_strlen(shell->line->line_data) + \
	ft_strlen(shell->yank)) / shell->win.ws_col) + 2;
	while (cpt--)
		tputs(tgetstr("up", NULL), 1, my_putchar);
}

static void		past_clear_line(t_shell *shell)
{
	int			cpt;

	cpt = 100;
	keyhome(shell);
	while (--cpt)
		tputs(tgetstr("le", NULL), 1, my_putchar);
	tputs(tgetstr("cd", NULL), 1, my_putchar);
}

static void		reput_line(t_shell *shell, int tmpp)
{
	int			cpt;

	put_color(shell);
	shell->cpt = (shell->pos / shell->win.ws_col) + 1;
	shell->pos = ft_strlen(shell->line->line_data);
	while (shell->pos > tmpp)
	{
		shell->cpt = (shell->pos / shell->win.ws_col) + 1;
		arrow_left(shell);
	}
	cpt = ft_strlen(shell->yank);
	shell->pos = tmpp;
	while (cpt--)
	{
		arrow_right(shell);
		shell->cpt = (shell->pos / shell->win.ws_col) + 1;
	}
	if (shell->pos == ft_strlen(shell->line->line_data))
		if (shell->pos == shell->win.ws_col * (shell->cpt - 1))
			tputs(tgetstr("do", NULL), 1, my_putchar);
}

int				start_past(char buffer[6], t_shell *shell)
{
	char		*tmp;
	char		*tmp2;
	int			tmpp;

	init_past(shell, &tmpp, buffer);
	put_color(shell);
	shell->pos = ft_strlen(shell->line->line_data);
	while (shell->pos != tmpp)
		arrow_left(shell);
	tmp = ft_strdup(shell->line->line_data);
	tmp[shell->pos] = '\0';
	tmp2 = ft_strjoinfree(tmp, shell->yank, 1, 0);
	tmp = ft_strdup(shell->line->line_data + shell->pos);
	tmp = ft_strjoinfree(tmp2, tmp, 1, 1);
	lt_release((void*)shell->line->line_data);
	shell->line->line_data = tmp;
	past_clear_line(shell);
	reput_line(shell, tmpp);
	return (0);
}
