/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_key_fonction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 20:44:34 by tblaudez          #+#    #+#             */
/*   Updated: 2018/12/15 20:53:30 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char		*trimstartsp(char *str, int len)
{
	char	*str2;
	char	*tmp;
	char	*fre;
	char	*tmp2;
	char	*fre2;

	str2 = ft_strdup(str);
	str2[len] = '\0';
	tmp = ft_strdup(str + len);
	fre = str2;
	fre2 = tmp;
	while (*tmp == ' ')
		tmp++;
	tmp2 = ft_strjoinfree(str2, tmp, 0, 0);
	lt_release((void*)fre);
	lt_release((void*)fre2);
	return (tmp2);
}

int			is_quote(char *str)
{
	int		i;
	int		cpt;

	i = 0;
	cpt = 0;
	while (str[i])
	{
		if (str[i++] == '"')
			cpt++;
	}
	if (cpt % 2 == 0)
		return (0);
	else
		return (1);
}

void		put_color(t_shell *shell)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_strdup(shell->line->line_data);
	str[shell->line->prompt_len + 1] = '\0';
	if (shell->col == 0)
		ft_fprintf(1, "{green}%s{eoc}", str);
	else
		ft_fprintf(1, "{red}%s{eoc}", str);
	ft_putstr(shell->line->line_data + shell->line->prompt_len + 1);
}

void		my_putstr(char *str, t_shell **shell)
{
	int		i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		(*shell)->pos++;
		i++;
	}
}

char		**ft_split_path(char *str)
{
	char	**ret;
	int		temp;
	int		i;

	i = -1;
	temp = 0;
	while (str[++i])
	{
		if (str[i] == '/')
			temp = i;
	}
	if (!(ret = (char **)ft_memalloc(sizeof(char *) * (3))))
		return (0);
	if (!(ret[0] = ft_strsub(str, 0, temp + 1)))
		return (0);
	if (ft_strlen(str + temp + 1))
	{
		if (!(ret[1] = ft_strsub(str + temp + 1, 0, ft_strlen(str + temp + 1))))
			return (0);
	}
	return (ret);
}
