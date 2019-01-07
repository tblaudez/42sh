/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 22:26:08 by mgazel            #+#    #+#             */
/*   Updated: 2018/12/15 20:48:38 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void		ft_read(t_shell *tmpp)
{
	ioctl(2, TIOCGWINSZ, &tmpp->win);
	tmpp->cpt = (tmpp->pos / tmpp->win.ws_col) + 1;
}

static int		ft_is_return(t_shell *tmpp, char pattern)
{
	int		i;
	char	*str;

	i = ft_strlen(tmpp->line->line_data);
	str = tmpp->line->line_data;
	if ((str[i - 2] == '&' && str[i - 3] == '&') || \
			(str[i - 2] == '|' && str[i - 3] == '|') || str[i - 2] == '\\')
		return (0);
	i = tmpp->line->prompt_len + 1;
	if (ft_quote(tmpp->line->line_data) == pattern)
	{
		while (i < ft_strlen(tmpp->line->line_data))
		{
			if (*(tmpp->line->line_data + i) == pattern)
				break ;
			i++;
		}
		if (quote_return_free(tmpp, i))
			return (1);
	}
	return (0);
}

static void		decision2(t_shell *tmpp, char input[6])
{
	if (input[0] == 27)
		arrow_key(input, tmpp);
	if (input[0] == 127)
		del_key(input, tmpp);
	if (input[0] == 9)
		autocomplet(input, tmpp);
}

static int		ft_decision(t_shell *tmpp, t_shell *shell,\
char input[6])
{
	if (input[0] == 10)
	{
		shell->line->line_data = ft_strjoinfree(shell->line->line_data, \
			tmpp->line->line_data + tmpp->line->prompt_len + 1, 1, 0);
		tmpp->line->line_data = ft_strjoinfree(tmpp->line->line_data, \
			"\n", 1, 0);
		ft_putstr_fd("\n", 0);
		return (2);
	}
	decision2(tmpp, input);
	if (input[0] <= 126 && input[0] >= 32)
		alpha_num(input, tmpp);
	if (input[0] == 4)
	{
		if (!ft_strlen(tmpp->line->line_data + tmpp->line->prompt_len + 1))
			return (0);
		ft_ctrl_d(input, tmpp);
	}
	return (1);
}

int				init_quote(char pattern, t_shell *shell)
{
	char	input[6];
	t_shell *tmpp;
	int		i;

	tmpp = init_shell(shell->envp);
	while (42)
	{
		init_line_quote(tmpp, pattern);
		while (42)
		{
			ft_memset(input, '\0', 6);
			read(0, input, 6);
			ft_read(tmpp);
			if ((i = ft_decision(tmpp, shell, input)) == 0)
				return (0);
			if (i == 2)
				break ;
		}
		if (ft_is_return(tmpp, pattern))
			return (1);
		shell->line->line_data = ft_strjoinfree(shell->line->line_data,\
				"\n", 1, 0);
	}
}
