/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glob_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 19:11:27 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/15 20:48:38 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int				ft_nb_joker(char *str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] == '{')
			c++;
		i++;
	}
	return (c);
}

char			**ft_patern_split(char *str)
{
	char	**table;
	int		index;
	int		start;
	int		i;

	i = 0;
	index = 0;
	table = (char **)(ft_memalloc(sizeof(char *) * (ft_nb_joker(str) + 2)));
	if (str[i] && str[i] == '{')
	{
		table[index++] = ft_strdup("");
		i++;
	}
	while (str[i])
	{
		start = i;
		while (str[i] && str[i] != '{')
			i++;
		if (start == i)
			table[index++] = ft_strdup("");
		else
			table[index++] = ft_strsub(str, start, i - start);
		i++;
	}
	return (table);
}

int				ft_is_metachar(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '|' || c == '&'
	|| c == ';' || c == '(' || c == ')' || c == '<' || c == '>');
}

int				ft_is_globchar(char c)
{
	return (c == '*' || c == '?' || c == '[' || c == ']'
	|| c == '{' || c == '}');
}
