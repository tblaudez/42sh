/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 01:47:47 by tblaudez          #+#    #+#             */
/*   Updated: 2018/12/15 20:48:38 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	syncronize_line(t_shell *shell)
{
	int		i;

	i = shell->pos;
	tputs(tgetstr("sc", NULL), 0, my_putchar);
	keyhome(shell);
	while (shell->pos-- > 0)
		tputs(tgetstr("le", NULL), 0, my_putchar);
	tputs(tgetstr("cd", NULL), 0, my_putchar);
	put_color(shell);
	shell->pos = i;
	tputs(tgetstr("rc", NULL), 0, my_putchar);
}

char	*addpos_line(char str, char *actu, int pos)
{
	int		i;
	char	*new;
	int		cpt;

	cpt = 0;
	i = 0;
	new = (char*)ft_memalloc(sizeof(char) * ft_strlen(actu) + 3);
	while (i < pos)
	{
		new[i] = actu[i];
		i++;
	}
	new[i + cpt++] = str;
	while (actu[i])
	{
		new[i + cpt] = actu[i];
		i++;
	}
	new[i + cpt] = '\0';
	return (new);
}

void	clear_line2(t_shell *shell)
{
	int i;

	i = 100;
	keyhome(shell);
	while (--shell->pos != 0)
		shell->line->line_data[shell->pos] = '\0';
	tputs(tgetstr("cd", NULL), 0, my_putchar);
	while (i-- != 0)
		tputs(tgetstr("le", NULL), 0, my_putchar);
}

void	del_inline(t_shell *shell)
{
	t_line	*line;
	char	*line_data;
	char	*tmp;
	int		i;

	i = 0;
	line = shell->line;
	line_data = line->line_data;
	if (line_data[shell->pos + 1])
	{
		tmp = &line_data[shell->pos + 1];
		while (tmp[i])
		{
			line_data[shell->pos + i] = tmp[i];
			i++;
		}
	}
	line_data[shell->pos + i] = '\0';
}

void	put_line(char *str, t_shell *shell)
{
	t_line	*line;
	char	*line_data;
	int		j;

	j = 0;
	line = shell->line;
	line_data = line->line_data;
	j = 0;
	while (str[j])
	{
		line_data[shell->pos] = str[j];
		j++;
		shell->pos++;
	}
	j = (int)ft_strlen(line_data);
	line_data[shell->pos] = '\0';
}
