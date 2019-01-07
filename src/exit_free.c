/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 01:13:07 by trponess          #+#    #+#             */
/*   Updated: 2018/12/15 20:53:30 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_free(t_shell *shell)
{
	int		i;

	i = 0;
	while (shell->envp[i])
		lt_release((void*)shell->envp[i++]);
	lt_release((void*)shell->envp);
	lt_release((void*)shell->line->line_data);
	lt_release((void*)shell->line);
	lt_release((void*)shell);
}

void	ft_exit(const char *err_msg)
{
	t_shell	*shell;

	ft_putendl_fd(err_msg, 2);
	shell = get_shell_struct(NULL);
	tcsetattr(STDOUT_FILENO, TCSANOW, &shell->term_save);
	lt_destroy();
	exit(EXIT_SUCCESS);
}
