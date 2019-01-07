/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 00:01:30 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/15 20:53:30 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static char		*ft_replace(char *str, int i, char *s)
{
	char	*tmp;

	tmp = ft_strnew(ft_strlen(str) + ft_strlen(s));
	ft_strncpy(tmp, str, i);
	ft_strcat(tmp, s);
	ft_strcat(tmp, str + i + 1);
	lt_release((void*)str);
	return (tmp);
}

static char		*ft_replace_str(char *str, int start, int size, char *s)
{
	char	*suffix;
	char	*new;

	new = ft_strsub(str, 0, start);
	str += start;
	suffix = ft_strsub(str, size + 1, ft_strlen(str + size + 1));
	new = ft_strjoinfree(new, s, 1, 0);
	new = ft_strjoinfree(new, suffix, 1, 0);
	lt_release((void*)suffix);
	lt_release((void*)str);
	return (new);
}

static char		*ft_handle_dlr(char *new, int i, t_shell *shell)
{
	char	*var;
	int		j;

	var = 0;
	j = 0;
	while (new[i + j]
			&& !ft_strchr(" #$%;*+,-./[]\\^{}~\'\"", new[i + j]))
		j++;
	var = ft_strsub(new, i, j);
	if (get_env(var, shell->envp))
		new = ft_replace_str(new, i - 1, j,
				get_env(var, shell->envp));
	lt_release((void*)var);
	return (new);
}

char			*ft_expansion(char *line, t_shell *shell)
{
	char	*new;
	int		quot;
	int		dquot;
	int		i;

	i = 0;
	quot = 0;
	dquot = 0;
	new = ft_strdup(line);
	while (new[i])
	{
		if (new[i] == '\'')
			quot = (quot) ? 0 : 1;
		else if (new[i] == '\"')
			dquot = (dquot) ? 0 : 1;
		if (!quot && !dquot && get_env("HOME", shell->envp) && new[i] == '~')
			new = ft_replace(new, i, get_env("HOME", shell->envp));
		else if (!quot && new[i] == '$' && !new[i + 1])
			break ;
		else if (!quot && new[i] == '$')
			new = ft_handle_dlr(new, ++i, shell);
		i++;
	}
	lt_release((void*)line);
	return (new);
}
