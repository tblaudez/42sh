/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifetime.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 17:57:19 by tblaudez          #+#    #+#             */
/*   Updated: 2018/12/15 20:54:22 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIFETIME_H
# define LIFETIME_H

typedef struct s_lt	t_lt;

struct				s_lt
{
	void	*ptr;
	t_lt	*next;
};

t_lt				*get_lifetime(t_lt	*new_ptr);
void				*lt_push(void *ptr);
void				lt_release(void *ptr);
void				lt_destroy(void);

#endif
