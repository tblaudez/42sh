/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trponess <trponess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 16:16:58 by tblaudez          #+#    #+#             */
/*   Updated: 2018/12/09 00:31:41 by trponess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FPRINTF_H
# define FT_FPRINTF_H

# include <stdarg.h>
# include <wchar.h>
# include "libft.h"

# define FLAGS		"#0- +"
# define LETTERS	"sSdoxcCpub"

# define HASH		(list->flags & (1 << 4))
# define ZERO		(list->flags & (1 << 3))
# define MINUS		(list->flags & (1 << 2))
# define SPACE		(list->flags & (1 << 1))
# define PLUS		(list->flags & 1)

typedef struct		s_printf
{
	char			flags;
	char			modif;
	int				width;
	int				preci;

}					t_printf;

void				ft_fprintf(int fd, char *format, ...);

char				*apply_hash(char *str, char conv);
char				*apply_zero(char *str, char conv);
char				*apply_minus(char *str);
char				*apply_space(char *str, char conv);
char				*apply_plus(char *str, char conv);

char				*calculate_unicode(char *ret, wchar_t value);
char				*get_string(va_list ap);
char				*get_char(va_list ap);
char				*get_pointer(va_list ap);

char				*get_decimal(va_list ap);
char				*get_hexa(va_list ap);
char				*get_octal(va_list ap);
char				*get_unsigned(va_list ap);
char				*get_binary(va_list ap);

int					find_end(char *format);
t_printf			*get_list_printf(int type);
int					set_modif(char *format);
char				*check_flags(char *format);
int					check_colors(char *format, int fd, int *i);
char				*apply_width(char *str, char conv);

char				*ft_uitoabase(unsigned int nbr, int base);
int					ft_unbrdig(unsigned int nbr, int base);

#endif
