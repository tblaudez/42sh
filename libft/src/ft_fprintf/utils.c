/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 17:19:15 by tblaudez          #+#    #+#             */
/*   Updated: 2018/12/15 20:53:30 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

t_printf	*get_list_printf(int type)
{
	static t_printf	*list = NULL;

	if (!list)
	{
		if (!(list = (t_printf*)ft_memalloc(sizeof(t_printf))))
			return (NULL);
		list->flags = 0;
		list->modif = 0;
		list->width = -1;
		list->preci = -1;
	}
	if (type == 1)
	{
		lt_release((void*)list);
		list = NULL;
	}
	return (list);
}

int			set_modif(char *format)
{
	t_printf	*list;
	int			i;

	list = get_list_printf(0);
	if (*(format + 1) != 'h' && *(format + 1) != 'l')
	{
		if ((i = ft_charsrc("hjzl", *format)) >= 0)
			list->modif |= (1 << (3 - i));
		return (0);
	}
	else if (*format == 'h' && *(format + 1) == 'h')
		list->modif |= (1 << 4);
	else if (*format == 'l' && *(format + 1) == 'l')
		list->modif |= (1 << 5);
	return (1);
}

char		*check_flags(char *format)
{
	t_printf	*list;
	int			i;

	list = get_list_printf(0);
	while (*format)
	{
		if (ft_strchr(LETTERS, *format))
			break ;
		else if (ft_strchr("hjzl", *format))
			format += set_modif(format);
		else if ((i = ft_charsrc(FLAGS, *format)) >= 0)
			list->flags |= (1 << (4 - i));
		else if (ft_isdigit(*format))
		{
			list->width = ft_atoi(format);
			format += (ft_nbrdig(list->width, 10) - 1);
		}
		else if (*format == '.')
		{
			list->preci = ft_atoi(format + 1);
			format += ft_nbrdig(list->preci, 10);
		}
		format++;
	}
	return (format);
}

int			check_colors(char *format, int fd, int *i)
{
	int			j;
	int			k;
	char		tmp[16];
	const char	*colors[14] = {"red", "green", "yellow", "blue", "magenta", \
		"cyan", "bold", "dim", "underlined", "blink", "reverse", "hidden", \
		"eoc", NULL};
	const char	*code[14] = {"\x1b[31m", "\x1b[32m", "\x1b[33m", "\x1b[34m", \
		"\x1b[35m", "\x1b[36m", "\x1b[1m", "\x1b[2m", "\x1b[4m", "\x1b[5m", \
		"\x1b[7m", "\x1b[8m", "\x1b[0m", NULL};

	k = *i;
	format += k;
	ft_strncpy(tmp, format + 1, ft_charsrc(format, '}') - 1);
	j = -1;
	while (colors[++j])
		if (ft_strequ(colors[j], tmp))
		{
			write(fd, format - k, k);
			ft_putstr_fd(code[j], fd);
			*i = -1;
			return (ft_strlen(tmp) + k + 2);
		}
	return (0);
}

char		*apply_width(char *str, char conv)
{
	t_printf	*list;
	int			i;
	char		*tmp;

	if (ft_strchr("SC", conv))
		return (str);
	list = get_list_printf(0);
	if (list->width <= ft_strlen(str))
		return (str);
	i = list->width - ft_strlen(str);
	list = get_list_printf(0);
	tmp = ft_strnew(i);
	ft_memset(tmp, ' ', i);
	return (ft_strjoinfree(tmp, str, 1, 1));
}
