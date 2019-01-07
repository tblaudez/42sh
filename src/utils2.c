/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 17:01:43 by tblaudez          #+#    #+#             */
/*   Updated: 2018/12/15 20:53:30 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		ft_is_type(const char *what, t_type type)
{
	if (ft_strequ(what, "redir"))
	{
		if (type == GRT || type == LSR || type == D_GRT \
		|| type == D_LSR || type == GRTAND || type == LSRAND)
			return (1);
		return (0);
	}
	else if (ft_strequ(what, "separator"))
	{
		if (type == PIPE || type == SEMICOLON || type == D_PIPE \
		|| type == D_AND || type == EOL)
			return (1);
		return (0);
	}
	return (0);
}

int		ft_is_in(const char *what, t_cmd *cmd_list)
{
	if (ft_strequ(what, "pipe"))
		return (cmd_list && cmd_list->next && cmd_list->next->flags & 1);
	else if (ft_strequ(what, "dand"))
		return (cmd_list && cmd_list->next && cmd_list->next->flags & (1 << 1));
	else if (ft_strequ(what, "dpipe"))
		return (cmd_list && cmd_list->next && cmd_list->next->flags & (1 << 2));
	return (0);
}

void	add_special_behavior(t_type type, t_cmd *cmd_list)
{
	if (type == PIPE)
		cmd_list->flags |= 1;
	else if (type == D_AND)
		cmd_list->flags |= (1 << 1);
	else if (type == D_PIPE)
		cmd_list->flags |= (1 << 2);
}

void	append_argument(char ***args_ptr, char *str)
{
	char	**array;
	char	**tmp;
	int		i;

	array = (*args_ptr);
	i = -1;
	if (!array)
	{
		array = (char**)ft_memalloc(sizeof(char*) * 2);
		array[0] = ft_strdup(str);
		*args_ptr = array;
		return ;
	}
	while (array[++i])
		continue ;
	tmp = (char**)ft_memalloc(sizeof(char*) * (i + 2));
	i = -1;
	while (array[++i])
		tmp[i] = array[i];
	tmp[i] = ft_strdup(str);
	lt_release((void*)array);
	(*args_ptr) = tmp;
}

void	append_to_redir_list(t_redir **ptr, char *from, char *to, t_type type)
{
	t_redir	*redir_list;

	redir_list = (*ptr);
	if (!redir_list)
	{
		redir_list = (t_redir*)ft_memalloc(sizeof(t_redir));
		redir_list->from = ft_strdup(from);
		redir_list->to = ft_strdup(to);
		redir_list->type = type;
		*ptr = redir_list;
		return ;
	}
	while (redir_list->next)
		redir_list = redir_list->next;
	redir_list->next = (t_redir*)ft_memalloc(sizeof(t_redir));
	redir_list = redir_list->next;
	redir_list->from = ft_strdup(from);
	redir_list->to = ft_strdup(to);
	redir_list->type = type;
}
