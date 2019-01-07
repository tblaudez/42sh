/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glob_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 15:53:53 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/15 20:53:30 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			ft_free_lst(t_match *match)
{
	t_match		*temp;

	while (match)
	{
		lt_release((void*)match->name);
		temp = match->next;
		lt_release((void*)match);
		match = temp;
	}
}

static t_match	*ft_match_new(char *name)
{
	t_match		*match;

	match = (t_match *)ft_memalloc(sizeof(t_match));
	match->name = ft_strdup(name);
	return (match);
}

t_match			*ft_match_add(char *name, t_match *match)
{
	t_match		*start;

	if (match == 0)
		return (ft_match_new(name));
	start = match;
	while (match->next)
		match = match->next;
	match->next = (t_match *)ft_memalloc(sizeof(t_match));
	match->next->name = ft_strdup(name);
	match = start;
	return (match);
}
