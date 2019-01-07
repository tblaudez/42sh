/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 23:58:17 by mgazel            #+#    #+#             */
/*   Updated: 2018/12/15 20:48:38 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_shell		*history_down_clear(t_shell *shell)
{
	clear_line2(shell);
	display_prompt(shell);
	return (shell);
}
