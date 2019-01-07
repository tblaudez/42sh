/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_function_alpha.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 22:19:57 by mgazel            #+#    #+#             */
/*   Updated: 2018/12/15 20:53:30 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void		alpha_reload_line(t_shell *shell)
{
	int		i;
	int		j;

	i = shell->pos;
	tputs(tgetstr("sc", NULL), 1, my_putchar);
	j = i;
	keyhome(shell);
	while (i-- >= 0)
		tputs(tgetstr("le", NULL), 1, my_putchar);
	tputs(tgetstr("cd", NULL), 1, my_putchar);
	put_color(shell);
	i = ft_strlen(shell->line->line_data);
	while (i-- > j)
		tputs(tgetstr("le", NULL), 1, my_putchar);
	shell->pos = j + 1;
	tputs(tgetstr("nd", NULL), 1, my_putchar);
}

void			alpha_inline(t_shell *shell, char buffer[3])
{
	char	*tmp;

	tmp = shell->line->line_data;
	shell->line->line_data = addpos_line(buffer[0], \
			shell->line->line_data, shell->pos);
	lt_release((void*)tmp);
	alpha_reload_line(shell);
	if (shell->pos == (shell->win.ws_col * shell->cpt))
	{
		tputs(tgetstr("do", NULL), 1, my_putchar);
		shell->cpt++;
	}
	shell->line->line_data[ft_strlen(shell->line->line_data)] = '\0';
}

void			alpha_endline(t_shell *shell, char buffer[3])
{
	shell->line->line_data = addpos_line(buffer[0], shell->line->line_data, \
			ft_strlen(shell->line->line_data));
	shell->pos++;
	shell->line->line_data[shell->pos] = '\0';
	if (shell->pos == shell->win.ws_col * shell->cpt)
	{
		tputs(tgetstr("do", NULL), 1, my_putchar);
		shell->cpt++;
	}
}
