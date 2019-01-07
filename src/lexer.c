/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 09:50:09 by tblaudez          #+#    #+#             */
/*   Updated: 2018/12/15 20:48:38 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int	look_for_words(t_token *tk_list, char *input)
{
	int	len;

	tk_list->type = WORD;
	len = 0;
	while (input[len] && !ft_strchr("|&;()<>\'\" ", input[len]))
	{
		if (input[len] == '\\' && input[len + 1])
		{
			ft_strcpy(input + len, input + len + 1);
			len++;
			continue ;
		}
		len++;
	}
	if (len == 0)
	{
		ft_fprintf(2, "21sh: syntax error near `%c`\n", input[len]);
		get_shell_struct(NULL)->col = 1;
		return (-1);
	}
	tk_list->lexeme = ft_strsub(input, 0, len);
	return (len);
}

static int	test_grt_lsr(t_token *tk_list, char *input)
{
	if (input[0] == '>')
	{
		tk_list->lexeme = ft_strdup("1");
		if (ft_strchr(">&", input[1]))
		{
			tk_list->type = (input[1] == '>' ? D_GRT : GRTAND);
			return (2);
		}
		tk_list->type = GRT;
		return (1);
	}
	if (input[0] == '<')
	{
		tk_list->lexeme = ft_strdup("0");
		if (ft_strchr("<&", input[1]))
		{
			tk_list->type = (input[1] == '<' ? D_LSR : GRTAND);
			return (2);
		}
		tk_list->type = LSR;
		return (1);
	}
	return (-1);
}

static int	test_digit(t_token *tk_list, char *input)
{
	if (input[1] == '>')
	{
		if (input[2] == '>')
			tk_list->type = D_GRT;
		else if (input[2] == '&')
			tk_list->type = GRTAND;
		else
			tk_list->type = GRT;
		tk_list->lexeme = ft_strndup(&input[0], 1);
		return (ft_strchr(">&", input[2]) ? 3 : 2);
	}
	else if (input[1] == '<')
	{
		if (input[2] == '>')
			tk_list->type = D_LSR;
		else if (input[2] == '&')
			tk_list->type = LSRAND;
		else
			tk_list->type = LSR;
		tk_list->lexeme = ft_strndup(&input[0], 1);
		return (ft_strchr("<&", input[2]) ? 3 : 2);
	}
	return (look_for_words(tk_list, input));
}

static int	look_for_redir(t_token *tk_list, char *input)
{
	if (ft_strchr("<>", input[0]))
		return (test_grt_lsr(tk_list, input));
	else if (ft_isdigit(input[0]))
		return (test_digit(tk_list, input));
	else if (input[0] == '&')
	{
		tk_list->lexeme = ft_strdup("&");
		if (ft_strnequ("&>", input, 2))
			tk_list->type = GRT;
		else if (ft_strnequ("&<", input, 2))
			tk_list->type = LSR;
		else if (ft_strnequ("&&", input, 2))
			tk_list->type = D_AND;
		else
			tk_list->type = S_ERROR;
		return (tk_list->type == S_ERROR ? 1 : 2);
	}
	return (-1);
}

t_token		*create_token_list(char *input)
{
	t_token	*tk_list;
	int		tk_len;

	tk_list = (t_token*)ft_memalloc(sizeof(t_token));
	while (ft_isspace(*input))
		input++;
	if (!*input)
		return (tk_list);
	else if (ft_strchr("<&>", *input) || ft_isdigit(*input))
		tk_len = look_for_redir(tk_list, input);
	else if (ft_strchr("\'\"", input[0]))
		tk_len = look_for_quotes(tk_list, input);
	else if (ft_strchr("|;", input[0]))
	{
		tk_list->type = (ft_strnequ("||", input, 2) ? D_PIPE : input[0]);
		tk_len = (tk_list->type == D_PIPE ? 2 : 1);
	}
	else
		tk_len = look_for_words(tk_list, input);
	if (tk_len < 0 || tk_len > ft_strlen(input) \
	|| !(tk_list->next = create_token_list(input + tk_len)))
		return (NULL);
	return (tk_list);
}
