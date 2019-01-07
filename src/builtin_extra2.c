/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_extra2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 13:47:26 by trponess          #+#    #+#             */
/*   Updated: 2018/12/15 20:53:30 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	display_env(char **ev)
{
	int i;

	i = 0;
	if (!ev)
		return ;
	while (ev[i])
		ft_fprintf(1, "%s\n", ev[i++]);
}

char	**add_to_env(int pos, char **ev, char *envvar)
{
	char	**new_ev;
	int		i;

	if (pos > -1)
	{
		lt_release((void*)ev[pos]);
		ev[pos] = ft_strdup(envvar);
		return (ev);
	}
	i = 0;
	while (ev[i])
		i++;
	if (!(new_ev = (char **)ft_memalloc(sizeof(char *) * (i + 2))))
		return (NULL);
	i = -1;
	while (ev[++i])
		new_ev[i] = ft_strdup(ev[i]);
	new_ev[i++] = ft_strdup(envvar);
	new_ev[i] = 0;
	ft_dmemdel(&ev);
	return (new_ev);
}

char	**remove_from_env(int pos, char **ev)
{
	char	**new_ev;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (pos == -1 || !ev)
		return (ev);
	while (ev[i])
		i++;
	if (!(new_ev = (char **)ft_memalloc(sizeof(char *) * i)))
		return (NULL);
	i = 0;
	while (ev[i])
	{
		if (pos == i)
			j++;
		new_ev[i++] = ft_strdup(ev[j++]);
	}
	ft_dmemdel(&ev);
	return (new_ev);
}

char	**ft_dup_env(char **ev)
{
	char	**new_ev;
	int		i;

	i = 0;
	while (ev[i])
		i++;
	if (!(new_ev = (char **)ft_memalloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = -1;
	while (ev[++i])
		new_ev[i] = ft_strdup(ev[i]);
	new_ev[i] = 0;
	return (new_ev);
}
