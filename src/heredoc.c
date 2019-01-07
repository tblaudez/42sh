/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 22:09:03 by mgazel            #+#    #+#             */
/*   Updated: 2018/12/15 20:53:30 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void		heredoc_init(t_shell **tmpp)
{
	*tmpp = init_shell(get_shell_struct(NULL)->envp);
	(*tmpp)->line->prompt_len = 9;
	(*tmpp)->pos = 10;
	get_shell_struct(*tmpp);
}

static void		heredoc_line_init(t_shell *tmpp, char **cmpp)
{
	tmpp->pos = 10;
	lt_release((void*)tmpp->line->line_data);
	tmpp->line->line_data = ft_strdup("heredoc > ");
	put_color(tmpp);
	*cmpp = (char *)ft_memalloc(sizeof(char) * LINE_MAX);
}

static int		heredoc_read_decision(t_shell *tmpp, char input[6], \
const char *pattern, int pipefd[2])
{
	int		i;

	i = 0;
	if (input[0] == 10)
	{
		if (!ft_strequ(tmpp->line->line_data + 10, pattern))
			ft_putstr_fd(tmpp->line->line_data + 10, pipefd[1]);
		ft_putstr_fd(input, 0);
		i = 1;
	}
	heredoc_read_decision2(tmpp, input);
	if (input[0] == 4)
	{
		if (ft_ctrl_d(NULL, tmpp))
		{
			lt_release((void*)tmpp->line->line_data);
			tmpp->line->line_data = \
			ft_strjoinfree("heredoc > ", (char *)pattern, 0, 0);
			i = 1;
		}
	}
	return (i);
}

static void		heredoc_read(t_shell *tmpp, int pipefd[2], const char *pattern)
{
	char	input[6];
	int		i;

	while (42)
	{
		ft_memset(input, '\0', 6);
		read(0, input, 6);
		ioctl(2, TIOCGWINSZ, &tmpp->win);
		i = heredoc_read_decision(tmpp, input, pattern, pipefd);
		if (i == 1)
			break ;
	}
}

void			init_heredoc(const char *pattern, t_redir **redir_ptr)
{
	int		pipefd[2];
	char	*cmpp;
	t_shell *tmpp;

	tmpp = NULL;
	heredoc_init(&tmpp);
	pipe(pipefd);
	while (42)
	{
		heredoc_line_init(tmpp, &cmpp);
		heredoc_read(tmpp, pipefd, pattern);
		if (ft_strequ(tmpp->line->line_data + 10, pattern))
		{
			ft_strdel(&cmpp);
			ft_free(tmpp);
			break ;
		}
		ft_putstr_fd("\n", pipefd[1]);
		ft_strdel(&cmpp);
	}
	append_to_redir_list(redir_ptr, ft_itoa(0), ft_itoa(pipefd[0]), GRTAND);
	close(pipefd[1]);
}
