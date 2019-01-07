/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glob_case.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 15:05:52 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/15 20:53:30 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static char			**ft_brace_cases(char *patern)
{
	char	**cases;
	char	*cut;
	int		i;

	i = 1;
	if (!patern[0])
		return (0);
	while (patern[i] && patern[i] != '}')
		i++;
	cut = ft_strsub(patern, 0, i);
	cases = ft_strsplit(cut, ',');
	lt_release((void*)cut);
	return (cases);
}

void				ft_case_tab(char *patern, t_gdata *gdata)
{
	int		index;
	int		i;

	i = 0;
	index = 0;
	gdata->case_tab =
	(char ***)ft_memalloc(sizeof(char **) * (ft_nbbrack(patern) + 1));
	while (patern[i])
	{
		if (patern[i] == '{')
			gdata->case_tab[index++] = ft_brace_cases(patern + i + 1);
		i++;
	}
}

void				ft_case_str(char *patern, t_gdata *gdata)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	gdata->case_str =
	(char *)(ft_memalloc(sizeof(char) * (ft_strlen(patern) + 1)));
	while (patern[i])
	{
		if (patern[i] == '{')
		{
			gdata->case_str[j++] = '{';
			while (patern[i] && patern[i] != '}')
				i++;
		}
		else
			gdata->case_str[j++] = patern[i];
		if (patern[i])
			i++;
	}
}
