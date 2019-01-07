/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_term.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 22:28:00 by mgazel            #+#    #+#             */
/*   Updated: 2018/12/15 20:48:38 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		clear_term(char buffer[6], t_shell *shell)
{
	int		tmp;

	tmp = shell->pos;
	(void)buffer;
	tputs(tgetstr("cl", NULL)		, 1, my_putchar);
	put_color(shell);
	shell->pos = ft_strlen(shell->line->line_data);
	while (shell->pos-- > tmp)
		tputs(tgetstr("le", NULL), 1, my_putchar);
	shell->pos++;
	return (0);
}
