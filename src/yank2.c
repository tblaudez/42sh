/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yank2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 22:58:20 by mgazel            #+#    #+#             */
/*   Updated: 2018/12/15 20:53:30 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		return_yank(t_shell *shell, int tmp, int cpt)
{
	if (ft_strlen(shell->yank))
		lt_release((void*)shell->yank);
	if (cpt > 0)
		shell->yank = ft_strndup(shell->line->line_data + tmp, cpt);
	else if (cpt < 0)
		shell->yank = ft_strndup(shell->line->line_data + tmp + cpt,\
				cpt * -1);
}
