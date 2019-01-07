/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 15:30:32 by tblaudez          #+#    #+#             */
/*   Updated: 2018/12/12 19:33:01 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

# include "ft_fprintf.h"
# include "get_next_line.h"
# include "lifetime.h"

/*
** Memory zone operation
*/
void					*ft_memset(void *s, int c, size_t n);
void					*ft_memmove(void *dst, const void *src, size_t len);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
void					*ft_memcpy(void *dst, const void *src, size_t n);
void					*ft_memalloc(size_t size);
void					ft_memdel(void **ap);
void					ft_bzero(void *s, size_t n);
/*
** String operation
*/
int						ft_strlen(const char *str);
char					*ft_strcpy(char *dst, const char *src);
char					*ft_strncpy(char *dst, const char *src, size_t len);
char					*ft_strcat(char *dst, const char *src);
char					*ft_strncat(char *dst, const char *src, size_t len);
int						ft_strcmp(const char *s1, const char *s2);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					*ft_strchr(char *s, int c);
char					*ft_strrchr(const char *s, int c);
char					*ft_strstr(const char *haystack, const char *needle);
size_t					ft_strlcat(char *dst, const char *src, size_t size);
char					*ft_strdup(const char *src);
char					*ft_strndup(char *str, size_t n);
char					*ft_strnstr(const char *haystack, const char *needle,\
size_t len);
char					*ft_strnew(size_t size);
void					ft_strdel(char **as);
int						ft_strequ(const char *s1, const char *s2);
int						ft_strnequ(const char *s1, const char *s2, size_t n);
char					*ft_strsub(const char *s, int start, size_t len);
char					*ft_strjoinfree(char *s1, char *s2, int free1,\
int free2);
char					*ft_strtrim(char *s);
char					**ft_strsplit(const char *s, char c);
int						ft_charsrc(const char *str, char c);
char					*ft_strreplace(char *str, char c1, char c2);
/*
** Character classification
*/
int						ft_isprint(int c);
int						ft_isalnum(int c);
int						ft_isalpha(int c);
int						ft_isupper(int c);
int						ft_islower(int c);
int						ft_isdigit(int c);
int						ft_isspace(int c);
int						ft_isascii(int c);
int						ft_str_is(int (*f)(int c), const char *str);
/*
** Output operation
*/
void					ft_putchar(char c);
void					ft_putstr(const char *s);
void					ft_putendl(const char *s);
void					ft_putchar_fd(char c, int fd);
void					ft_putstr_fd(const char *s, int fd);
void					ft_putendl_fd(const char *s, int fd);
void					ft_putstrarray(char **array);
/*
** Utility
*/
int						ft_atoi(const char *str);
char					*ft_itoa(int n);
char					*ft_itoabase(int n, int base);
int						ft_atoibase(const char *str, int base);
int						ft_nbrdig(int n, int base);
int						ft_power(int nbr, int pow);
void					ft_strarraydel(char ***ptr);

#endif
