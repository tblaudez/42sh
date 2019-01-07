/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yank.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 16:49:24 by mgazel            #+#    #+#             */
/*   Updated: 2018/12/15 20:48:38 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void		re_put_all(t_shell *shell, int tmp)
{
	tputs(tgetstr("rc", NULL), 1, my_putchar);
	keyhome(shell);
	shell->pos = tmp;
	while (shell->pos--)
		tputs(tgetstr("le", NULL), 1, my_putchar);
	tputs(tgetstr("cd", NULL), 1, my_putchar);
	put_color(shell);
	tputs(tgetstr("rc", NULL), 1, my_putchar);
	shell->pos = tmp;
}

static void		select_yank_right(t_shell *shell, int *cpt)
{
	if (ft_strlen(shell->line->line_data + shell->pos + *cpt))
	{
		if (*cpt >= 0)
			ft_fprintf(1, "{reverse}%c{eoc}",\
					shell->line->line_data[shell->pos + *cpt]);
		if (*cpt < 0)
			ft_putchar(shell->line->line_data[shell->pos + *cpt]);
		(*cpt)++;
	}
}

static void		select_yank_left(t_shell *shell, int *cpt)
{
	if (shell->pos + *cpt > shell->line->prompt_len + 1)
	{
		tputs(tgetstr("le", NULL), 1, my_putchar);
		if (--(*cpt) >= 0)
		{
			ft_putchar(shell->line->line_data[shell->pos + *cpt]);
			tputs(tgetstr("le", NULL), 1, my_putchar);
		}
		if (*cpt < 0)
		{
			ft_fprintf(1, "{reverse}%c{eoc}",\
					shell->line->line_data[shell->pos + *cpt]);
			tputs(tgetstr("le", NULL), 1, my_putchar);
		}
	}
}

void			init_yank(int *tmp, int *cpt, t_shell *shell)
{
	*tmp = shell->pos;
	*cpt = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	tputs(tgetstr("sc", NULL), 1, my_putchar);
}

int				start_yank(char buffer[3], t_shell *shell)
{
	int			tmp;
	int			cpt;

	init_yank(&tmp, &cpt, shell);
	while (42)
	{
		read(0, buffer, 3);
		if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 67)
			select_yank_right(shell, &cpt);
		else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 68)
			select_yank_left(shell, &cpt);
		else
		{
			return_yank(shell, tmp, cpt);
			break ;
		}
	}
	re_put_all(shell, tmp);
	ft_catchsign();
	return (0);
}
