/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glob_check_patern.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 19:54:08 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/15 20:48:38 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int		ft_check_bracket_patern(char *bracket, char c)
{
	int		not;
	int		i;

	i = 0;
	not = 0;
	if (bracket[i] == '!')
	{
		not = 1;
		i++;
	}
	while (bracket[i] && bracket[i] != ']')
	{
		if (bracket[i + 1] && bracket[i + 1] == '-' && bracket[i + 2])
		{
			if (c >= bracket[i] && c <= bracket[i + 2])
				return ((not) ? 0 : 1);
			else
				i += 2;
		}
		if (c == bracket[i])
			return ((not) ? 0 : 1);
		i++;
	}
	return ((not) ? 1 : 0);
}

int				ft_check_patern(char *patern, char *element, int i, int j)
{
	if (!patern[i])
		return ((!element[j]) ? 1 : 0);
	else if (patern[i] == '[')
	{
		if (ft_check_bracket_patern(patern + i + 1, element[j]))
		{
			while (patern[i] && patern[i] != ']')
				i++;
			return (ft_check_patern(patern, element, i + 1, j + 1));
		}
		return (0);
	}
	else if (patern[i] == '*')
	{
		while (element[j])
			if (ft_check_patern(patern, element, i + 1, j++))
				return (1);
		return (ft_check_patern(patern, element, i + 1, j));
	}
	else if (patern[i] != '?' && patern[i] != element[j])
		return (0);
	if (element[j])
		return (ft_check_patern(patern, element, i + 1, j + 1));
	return (0);
}
