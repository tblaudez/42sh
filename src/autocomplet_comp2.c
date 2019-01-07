/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplet_comp2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 17:50:58 by mgazel            #+#    #+#             */
/*   Updated: 2018/12/15 20:48:38 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			comp_dir_whit_slash(t_shell *shell, t_auto *autoo)
{
	autoo->tabb = ft_split_path(autoo->lastword);
	autoo->dirr = opendir(autoo->tabb[0]);
	if (autoo->dirr)
		shell->lastword = autoo->tabb[1];
}

int				comp_check_dir(t_auto *autoo)
{
	if (autoo->dirr == NULL)
		autoo->dirr = opendir(".");
	if (autoo->dirr == NULL)
		return (0);
	return (1);
}

void			comp_add_and_cmp(t_shell *shell, t_auto *autoo)
{
	add_tk(&shell->autoc, autoo->l->d_name, autoo->l->d_type);
	if (ft_strncmp(shell->lastword, autoo->l->d_name, \
	ft_strlen(shell->lastword)) == 0)
		shell->autoc->is_cmp = 1;
}
