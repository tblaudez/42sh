/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glob_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 16:57:48 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/15 20:53:30 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static char		*ft_get_next_word(char **line_ptr)
{
	int		pos;
	int		ok;
	int		i;

	ok = 0;
	while (**line_ptr)
	{
		i = 0;
		pos = 0;
		while ((*line_ptr)[pos] && !ft_is_metachar((*line_ptr)[pos]))
		{
			if (ft_is_globchar((*line_ptr)[pos++]))
				ok = 1;
		}
		if (ok == 1)
			return (ft_strsub((*line_ptr), 0, pos));
		while (**line_ptr && i++ < (pos + 1))
			(*line_ptr)++;
	}
	return (0);
}

static void		ft_init_word(char *word, t_gdata *gdata)
{
	gdata->glob_lst = 0;
	gdata->path = ft_strdup("");
	gdata->endslash = (word[ft_strlen(word) - 1] == '/') ? 1 : 0;
	gdata->startslash = (word[0] == '/') ? 1 : 0;
	gdata->samples = ft_strsplit(word, '/');
}

void			ft_glob_process(t_shell *shell)
{
	char		*line_ptr;
	char		*word;
	t_gdata		gdata;

	ft_bzero(&gdata, sizeof(t_gdata));
	shell->line->line_data = ft_expansion(shell->line->line_data, shell);
	shell->line->line_data = ft_remove_mult(shell->line->line_data);
	line_ptr = shell->line->line_data;
	gdata.new_line = ft_strdup(line_ptr);
	while ((word = ft_get_next_word(&line_ptr)))
	{
		ft_init_word(word, &gdata);
		ft_glob_loop(gdata.samples, &gdata);
		if (gdata.glob_lst)
			ft_new_line_data(word, &gdata);
		line_ptr += ft_strlen(word);
		ft_free_lst(gdata.glob_lst);
		ft_tabdel(gdata.samples);
		lt_release((void*)gdata.path);
		lt_release((void*)word);
		gdata.endslash = 0;
	}
	lt_release((void*)shell->line->line_data);
	shell->line->line_data = gdata.new_line;
}
