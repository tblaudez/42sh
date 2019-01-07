/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 23:09:26 by mgazel            #+#    #+#             */
/*   Updated: 2018/12/15 20:53:30 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		init_line_quote(t_shell *tmpp, char pattern)
{
	get_shell_struct(tmpp);
	lt_release((void*)tmpp->line->line_data);
	if (pattern == '"')
	{
		tmpp->line->line_data = ft_strdup("pquote > ");
		tmpp->pos = 9;
		tmpp->line->prompt_len = 8;
	}
	else if (pattern == '\'')
	{
		tmpp->line->line_data = ft_strdup("quote > ");
		tmpp->pos = 8;
		tmpp->line->prompt_len = 7;
	}
	else if (pattern == '\n')
	{
		tmpp->line->line_data = ft_strdup(" > ");
		tmpp->pos = 3;
		tmpp->line->prompt_len = 2;
	}
	put_color(tmpp);
}

int			quote_return_free(t_shell *tmpp, int i)
{
	if (i < ft_strlen(tmpp->line->line_data))
	{
		ft_free(tmpp);
		return (1);
	}
	return (0);
}
