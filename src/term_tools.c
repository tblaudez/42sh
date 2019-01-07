/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 09:57:59 by tblaudez          #+#    #+#             */
/*   Updated: 2018/12/15 20:48:38 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		my_putchar(int c)
{
	ft_putchar((char)c);
	return (1);
}

void	ft_clear(void)
{
	char *res;

	if ((res = tgetstr("cl", NULL)) == NULL)
		return ;
	tputs(res, 1, my_putchar);
}

void	ft_ul_video(char *str)
{
	tputs(tgetstr("us", NULL), 1, my_putchar);
	tputs(tgetstr("mr", NULL), 1, my_putchar);
	ft_putstr(str);
	tputs(tgetstr("me", NULL), 1, my_putchar);
	tputs(tgetstr("ue", NULL), 1, my_putchar);
}

void	ft_ul(char *str)
{
	tputs(tgetstr("us", NULL), 1, my_putchar);
	ft_putstr(str);
	tputs(tgetstr("ue", NULL), 1, my_putchar);
}

void	ft_video(char *str)
{
	tputs(tgetstr("mr", NULL), 1, my_putchar);
	ft_putstr(str);
	tputs(tgetstr("me", NULL), 1, my_putchar);
}
