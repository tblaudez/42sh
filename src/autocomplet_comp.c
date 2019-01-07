/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplet_comp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 17:48:04 by mgazel            #+#    #+#             */
/*   Updated: 2018/12/15 20:48:38 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			add_tk(t_complet **list, char *name, unsigned char type)
{
	t_complet	*new;

	new = (t_complet *)ft_memalloc(sizeof(t_complet));
	new->is_cmp = 0;
	new->is_select = 0;
	new->type = type;
	new->name = ft_strdup(name);
	new->next = *list;
	*list = new;
}

void			init_comp(t_shell *shell, t_auto *autoo)
{
	autoo->i = 0;
	keyend(shell);
	autoo->cpt = shell->pos;
	shell->autoc = NULL;
	while (shell->line->line_data[shell->pos - 1] != ' ')
		shell->pos--;
}

int				comp_path(t_shell *shell, t_auto *autoo)
{
	shell->lastword = ft_strdup(&shell->line->line_data[shell->pos]);
	if (get_env("PATH", shell->envp) != NULL)
		autoo->tabb = ft_strsplit(get_env("PATH", shell->envp), ':');
	else
	{
		shell->pos = autoo->cpt;
		return (0);
	}
	while (autoo->tabb[autoo->i])
	{
		if ((autoo->dirr = opendir(autoo->tabb[autoo->i])))
			while ((autoo->l = readdir(autoo->dirr)))
			{
				add_tk(&shell->autoc, autoo->l->d_name, autoo->l->d_type);
				if (ft_strncmp(shell->lastword, autoo->l->d_name, \
				ft_strlen(shell->lastword)) == 0)
					shell->autoc->is_cmp = 1;
			}
		if (autoo->dirr)
			closedir(autoo->dirr);
		autoo->i++;
	}
	shell->pos = autoo->cpt;
	return (1);
}

void			comp_dir_whitout_slash(t_shell *shell, t_auto *autoo)
{
	autoo->tmp = ft_strjoinfree("./", shell->lastword, 0, 0);
	autoo->tabb = ft_split_path(autoo->tmp);
	autoo->dirr = opendir(autoo->tabb[0]);
	if (autoo->dirr)
		shell->lastword = autoo->tabb[1];
}

int				start_comp(t_shell *shell)
{
	t_auto			autoo;

	init_comp(shell, &autoo);
	if (shell->pos == shell->line->prompt_len + 1)
		return (comp_path(shell, &autoo));
	autoo.lastword = &shell->line->line_data[shell->pos];
	shell->autoc = NULL;
	shell->lastword = ft_strdup(autoo.lastword);
	if (*(autoo.lastword) != '/')
		comp_dir_whitout_slash(shell, &autoo);
	else
		comp_dir_whit_slash(shell, &autoo);
	if (!comp_check_dir(&autoo))
		return (0);
	while ((autoo.l = readdir(autoo.dirr)))
		comp_add_and_cmp(shell, &autoo);
	closedir(autoo.dirr);
	shell->pos = autoo.cpt;
	return (1);
}
