/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplet_select.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 18:00:47 by mgazel            #+#    #+#             */
/*   Updated: 2018/12/15 20:48:38 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int		check_struct(t_shell *shell, t_complet *tmp)
{
	if (tmp == NULL && !tmp)
	{
		tmp = shell->autoc;
		if (tmp == NULL)
			return (1);
	}
	return (0);
}

static void		clear_select(void)
{
	tputs(tgetstr("rc", NULL), 1, my_putchar);
	tputs(tgetstr("cd", NULL), 1, my_putchar);
	ft_putchar('\n');
}

static int		return_select(t_shell *shell, t_complet *tmp)
{
	if (tmp->type == DT_DIR)
		tmp->name = ft_strjoinfree(tmp->name, "/", 1, 0);
	tputs(tgetstr("rc", NULL), 1, my_putchar);
	my_putstr(tmp->name + ft_strlen(shell->lastword), &shell);
	shell->line->line_data = ft_strjoinfree(shell->line->line_data,\
			tmp->name + ft_strlen(shell->lastword), 0, 0);
	tputs(tgetstr("sc", NULL), 1, my_putchar);
	t_free(shell->autoc);
	return (1);
}

static int		return_other_key(t_shell *shell, char buffer[6])
{
	tputs(tgetstr("rc", NULL), 1, my_putchar);
	tputs(tgetstr("cd", NULL), 1, my_putchar);
	if (buffer[0] > 0 && *shell->line->line_data == '[')
		(shell->key_function[(int)buffer[0]])(buffer, shell);
	tputs(tgetstr("sc", NULL), 1, my_putchar);
	t_free(shell->autoc);
	return (0);
}

int				start_select(t_shell *shell)
{
	char		buffer[6];
	t_complet	*tmp;
	int			i;

	tmp = shell->autoc;
	while (42)
	{
		if (check_struct(shell, tmp))
			return (1);
		if (tmp && tmp->is_cmp == 1)
		{
			if (set_and_display(shell, &tmp) == 1)
				return (1);
			read(0, buffer, 6);
			if (buffer[0] == 9)
				clear_select();
			if (buffer[0] == 10)
				return (return_select(shell, tmp));
			if (buffer[0] != 9)
				return (return_other_key(shell, buffer));
			i = 1;
		}
		if (!unset_and_next(&tmp))
			return (1);
	}
}
