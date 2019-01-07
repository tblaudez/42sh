/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplet.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 14:39:31 by mgazel            #+#    #+#             */
/*   Updated: 2018/12/15 20:53:30 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			t_free(t_complet *list)
{
	t_complet	*tmp;

	tmp = list;
	while (list->next)
	{
		if (list->next)
			tmp = list->next;
		list->is_cmp = 0;
		if (list->name)
			lt_release((void*)list->name);
		lt_release((void*)list);
		list = tmp;
	}
	if (tmp)
	{
		lt_release((void*)tmp->name);
		lt_release((void*)tmp);
	}
}

void			display_select(t_complet *list)
{
	t_complet	*tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->is_select == 1 && tmp->is_cmp == 1)
			ft_fprintf(1, "{red}%s{eoc} ", tmp->name);
		if (tmp->is_select == 0 && tmp->is_cmp == 1)
			ft_fprintf(1, "%s ", tmp->name);
		tmp = tmp->next;
	}
}

int				cpt_comp(t_complet *list)
{
	int			cpt;
	t_complet	*tmp;

	if (!list)
		return (0);
	tmp = list;
	cpt = 0;
	while (tmp->next)
	{
		if (tmp && tmp->name && tmp->is_cmp)
			cpt = cpt + ft_strlen(tmp->name) + 1;
		tmp = tmp->next;
	}
	return ((cpt / get_shell_struct(NULL)->win.ws_col) + 1);
}

int				autocomplet(char buffer[6], t_shell *shell)
{
	int			i;

	if (!ft_strlen(shell->line->line_data + shell->line->prompt_len + 1))
		return (0);
	if (!start_comp(shell))
		return (0);
	signal(SIGINT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	keyend(shell);
	i = cpt_comp(shell->autoc);
	while (i--)
		ft_putchar('\n');
	while (++i != cpt_comp(shell->autoc))
		tputs(tgetstr("up", NULL), 1, my_putchar);
	put_color(shell);
	tputs(tgetstr("sc", NULL), 1, my_putchar);
	ft_putchar('\n');
	(void)buffer;
	if (start_select(shell) == 1)
	{
		tputs(tgetstr("rc", NULL), 1, my_putchar);
		tputs(tgetstr("cd", NULL), 1, my_putchar);
	}
	ft_catchsign();
	return (0);
}
