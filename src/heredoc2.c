/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 22:11:47 by mgazel            #+#    #+#             */
/*   Updated: 2018/12/15 20:48:38 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		heredoc_read_decision2(t_shell *tmpp, char input[6])
{
	if (input[0] <= 126 && input[0] >= 32)
		alpha_num(input, tmpp);
	if (input[0] == 27)
		arrow_key(input, tmpp);
	if (input[0] == 127)
		del_key(input, tmpp);
}
