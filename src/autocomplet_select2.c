/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplet_select2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 18:21:49 by mgazel            #+#    #+#             */
/*   Updated: 2018/12/15 20:48:38 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int				unset_and_next(t_complet **tmp)
{
	if (!(*tmp))
		return (0);
	if (*tmp)
		(*tmp)->is_select = 0;
	if (*tmp)
		(*tmp) = (*tmp)->next;
	return (1);
}

int				set_and_display(t_shell *shell, t_complet **tmp)
{
	if (*tmp == NULL)
		return (1);
	(*tmp)->is_select = 1;
	display_select(shell->autoc);
	return (0);
}
