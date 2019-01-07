/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 15:07:36 by tblaudez          #+#    #+#             */
/*   Updated: 2018/12/15 20:48:38 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void		add_redirection(t_token **tk_ptr, t_redir **redir_ptr)
{
	const t_type	type = (*tk_ptr)->type;
	const char		*file = (*tk_ptr)->next->lexeme;
	t_shell			*shell;

	shell = get_shell_struct(NULL);
	if (type == GRT || type == D_GRT || type == LSR || type == GRTAND)
		append_to_redir_list(redir_ptr, (*tk_ptr)->lexeme, (char*)file, type);
	else if (type == LSRAND)
		append_to_redir_list(redir_ptr, (char*)file, (*tk_ptr)->lexeme, type);
	else if (type == D_LSR)
	{
		init_heredoc(file, redir_ptr);
		get_shell_struct(shell);
	}
	(*tk_ptr) = (*tk_ptr)->next;
}

t_cmd			*create_cmd_list(t_token *tk_list)
{
	t_cmd	*cmd_list;
	t_cmd	*first_node;

	if (!check_syntax_error(tk_list) && (get_shell_struct(NULL)->col = 1))
	{
		ft_putendl_fd("21sh: Syntax error", 2);
		return (NULL);
	}
	cmd_list = (t_cmd*)ft_memalloc(sizeof(t_cmd));
	first_node = cmd_list;
	while (tk_list && tk_list->type != EOL)
	{
		if (ft_is_type("separator", tk_list->type))
		{
			cmd_list->next = (t_cmd*)ft_memalloc(sizeof(t_cmd));
			add_special_behavior(tk_list->type, cmd_list->next);
			cmd_list = cmd_list->next;
		}
		else if (ft_is_type("redir", tk_list->type))
			add_redirection(&tk_list, &cmd_list->redir);
		else
			append_argument(&cmd_list->args, tk_list->lexeme);
		tk_list = tk_list->next;
	}
	return (first_node);
}
