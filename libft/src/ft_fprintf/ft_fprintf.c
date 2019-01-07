/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 22:46:40 by tblaudez          #+#    #+#             */
/*   Updated: 2018/10/11 15:11:40 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

static char	*apply_precision(char *str, char conv)
{
	t_printf	*list;
	int			i;
	char		*tmp;

	list = get_list_printf(0);
	if (!ft_strchr("diouxXs", conv))
		return (str);
	if (conv == 's')
		return (ft_strncpy(str, str, list->preci));
	if ((i = list->preci - ft_strlen(str)) <= 0)
		return (str);
	tmp = ft_strnew(i);
	ft_memset(tmp, '0', i);
	str = ft_strjoinfree(tmp, str, 1, 1);
	if (conv == 'd' && ft_strchr(str, '-'))
	{
		str = ft_strreplace(str, '-', '0');
		str = ft_strjoinfree("0", str, 0, 1);
		str[0] = '-';
	}
	return (str);
}

static char	*apply_flags(char *str, char conv)
{
	t_printf	*list;

	list = get_list_printf(0);
	if (list->preci != -1)
		str = apply_precision(str, conv);
	if (HASH)
		str = apply_hash(str, conv);
	if (MINUS)
		str = apply_minus(str);
	else if (ZERO)
		str = apply_zero(str, conv);
	if (PLUS)
		str = apply_plus(str, conv);
	else if (SPACE)
		str = apply_space(str, conv);
	if (!MINUS && !ZERO && list->width != -1)
		str = apply_width(str, conv);
	return (str);
}

static char	*conversion(char *format, va_list ap)
{
	t_printf	*list;
	int			i;
	char		*(*const func[10])(va_list ap) = {&get_string, &get_string,\
		&get_decimal, &get_octal, &get_hexa, &get_char, &get_char,\
		&get_pointer, &get_unsigned, &get_binary};

	list = get_list_printf(0);
	format = check_flags(format + 1);
	if (*format == 'C' || *format == 'S')
		list->modif |= 1;
	if ((i = ft_charsrc(LETTERS, *format)) >= 0)
		return (apply_flags(func[i](ap), *format));
	return (apply_flags(get_decimal(ap), *format));
}

static int	print_format(char *format, int i, int fd, va_list ap)
{
	char	*str;
	int		j;

	write(fd, format, i);
	str = conversion(format + i, ap);
	ft_putstr_fd(str, fd);
	ft_strdel(&str);
	get_list_printf(1);
	j = 0;
	while (!ft_strchr(LETTERS, format[j + i + 1]))
		j++;
	return (i + j + 2);
}

void		ft_fprintf(int fd, char *format, ...)
{
	va_list	ap;
	int		i;

	va_start(ap, format);
	i = 0;
	while (format[i])
	{
		if (format[i] == '{')
			format += check_colors(format, fd, &i);
		else if (format[i] == '%')
		{
			format += print_format(format, i, fd, ap);
			i = -1;
		}
		i++;
	}
	ft_putstr_fd(format, fd);
	va_end(ap);
}
