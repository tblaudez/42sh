/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glob_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 19:58:47 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/15 20:53:30 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char			*ft_remove_mult(char *word)
{
	int	i;

	i = -1;
	while (word[++i])
	{
		while (word[i] == '*' && word[i + 1] == '*')
		{
			ft_memmove(word + i, word + i + 1, ft_strlen(word + i + 1));
			word[ft_strlen(word) - 1] = 0;
		}
	}
	return (word);
}

int				ft_glob_brackets(char *str)
{
	int		state;
	int		i;

	i = 0;
	state = 2;
	while (str[i])
	{
		if (str[i] == '[' && (state == 0 || state == 2))
			state = 1;
		else if (str[i] == '[' && state == 1)
			return (-1);
		else if (str[i] == ']' && state == 0)
			return (-1);
		else if (str[i] == ']' && state == 1)
			state = 0;
		else if (state == 1 && (str[i] == '}' || str[i] == '{'))
			return (-1);
		i++;
	}
	if (state == 2)
		return (0);
	if (state == 0)
		return (1);
	return (-1);
}

int				ft_glob_braces(char *str)
{
	int		state;
	int		i;

	i = 0;
	state = 2;
	while (str[i])
	{
		if (str[i] == '{' && (state == 0 || state == 2))
			state = 1;
		else if (str[i] == '{' && state == 1)
			return (-1);
		else if (str[i] == '}' && state == 0)
			return (-1);
		else if (str[i] == '}' && state == 1)
			state = 0;
		else if (state == 1 && (str[i] == ']' || str[i] == '['))
			return (-1);
		i++;
	}
	if (state == 2)
		return (0);
	if (state == 0)
		return (1);
	return (-1);
}

int				ft_nbbrack(char *str)
{
	int		i;
	int		c;

	c = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '[' || str[i] == '{')
			c++;
		i++;
	}
	return (c);
}

void			ft_tabdel(char **table)
{
	int		i;

	i = 0;
	while (table[i])
		lt_release((void*)table[i++]);
	lt_release((void*)table);
}
