/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh42.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 09:05:39 by tblaudez          #+#    #+#             */
/*   Updated: 2018/12/15 20:49:19 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH42_H
# define SH42_H

/*
**	Include system's headers
*/

# include <limits.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <termcap.h>
# include <term.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <errno.h>
# include <inttypes.h>
# include <sys/mman.h>

/*
**	Include custom headers
*/

# include "libft.h"
# include "lifetime.h"

/*
**	tblaudez: lexer / parser / redirections / execution
*/

typedef struct s_redir		t_redir;
typedef struct s_cmd		t_cmd;
typedef struct s_token		t_token;
typedef enum e_tokentype	t_type;

enum					e_tokentype
{
	SEMICOLON = ';', PIPE = '|', QUOTE = '\'',
	D_QUOTE = '\"', GRT = '>', LSR = '<',
	EOL = 0, WORD, D_GRT, D_LSR, LSRAND, \
	GRTAND, D_AND, D_PIPE, S_ERROR
};

struct					s_redir
{
	char	*from;
	char	*to;
	t_type	type;
	t_redir	*next;
};

struct					s_cmd
{
	char	**args;
	t_redir	*redir;
	char	flags;
	t_cmd	*next;
};

struct					s_token
{
	t_type				type;
	char				*lexeme;
	t_token				*next;
};

t_token					*create_token_list(char *input);
t_cmd					*create_cmd_list(t_token *tk_list);
void					shell_exec(t_cmd *cmd_list, char **envp);
int						launch_binary(char **cmd, char **envp);
void					free_tk_list(t_token *tk_list);
void					free_cmd_list(t_cmd *cmd_list);
void					append_to_redir_list(t_redir **ptr, char *from, \
						char *to, t_type type);
void					append_argument(char ***args_ptr, char *str);
int						check_syntax_error(t_token *tk_list);
void					add_special_behavior(t_type type,
						t_cmd *cmd_list);
int						ft_is_type(const char *what, t_type type);
int						ft_is_in(const char *what, t_cmd *cmd_list);
int						look_for_quotes(t_token *tk_list, char *input);
void					close_all(t_redir *redir_list);
t_cmd					*check_success(pid_t pid, t_cmd *cmd_list);

/*
**	mgazel: line edit / completion / history
*/

# define LINE_LEN 64

typedef struct			s_history
{
	char				*command;
	int					old;
	struct s_history	*next;
	struct s_history	*prev;
}						t_history;

typedef struct			s_line
{
	char				*line_data;
	int					prompt_len;
}						t_line;

typedef struct			s_complet
{
	char				*name;
	int					is_cmp;
	int					is_select;
	unsigned char		type;
	struct s_complet	*next;
}						t_complet;

typedef struct			s_shell
{
	int					col;
	char				*lastword;
	struct s_complet	*autoc;
	struct termios		term;
	struct termios		term_save;
	struct winsize		win;
	int					(*key_function[128])(char buffer[3],
						struct s_shell *shell);
	t_line				*line;
	int					pos;
	char				**envp;
	char				*yank;
	t_history			*history;
	t_history			*hist_ptr;
	char				**command;
	t_token				*token;
	t_cmd				*cmd;
	int					tty;
	int					cpt;
}						t_shell;

typedef struct			s_auto
{
	DIR					*dirr;
	struct dirent		*l;
	int					cpt;
	char				*lastword;
	char				*tmp;
	char				**tabb;
	int					i;
}						t_auto;

int						other_key(char buffer[6], t_shell *shell);
void					init_term(struct termios *term);
t_shell					*history_down_clear(t_shell *shell);
void					add_history_live(t_history *temp, \
						t_shell *shell, int i, char *command);
int						return_key_quote(t_shell *shell, char c);
int						quote_return_free(t_shell *tmpp, int i);
void					init_line_quote(t_shell *tmpp, char pattern);
void					return_yank(t_shell *shell, int tmp, int cpt);
void					heredoc_read_decision2(t_shell *tmpp, char input[6]);
void					init_heredoc(const char *pattern, t_redir **redir_ptr);
void					t_free(t_complet *list);
void					display_select(t_complet *list);
int						unset_and_next(t_complet **tmp);
int						set_and_display(t_shell *shell, t_complet **tmp);
int						start_select(t_shell *shell);
void					add_tk(t_complet **list, char *name, \
						unsigned char type);
int						start_comp(t_shell *shell);
void					comp_add_and_cmp(t_shell *shell, t_auto *autoo);
int						comp_check_dir(t_auto *autoo);
void					comp_dir_whit_slash(t_shell *shell, t_auto *autoo);
int						autocomplet(char buffer[6], t_shell *shell);
int						clear_term(char buffer[6], t_shell *shell);
int						start_past(char buffer[6], t_shell *shell);
int						start_yank(char buffer[6], t_shell *shell);
char					ft_quote(char *str);
void					alpha_inline(t_shell *shell, char buffer[3]);
void					alpha_endline(t_shell *shell, char buffer[3]);
void					arrow_left_ctrl(t_shell *shell);
void					arrow_left(t_shell *shell);
void					arrow_right_ctrl(t_shell *shell);
void					arrow_right(t_shell *shell);
void					return_final_line(t_shell *line);
void					return_exec(t_shell *shell);
void					return_history(t_shell *shell);
int						check_line_live(t_shell *shell);
void					set_terminal(struct termios term);
int						ft_ctrl_d(char buffer[6], t_shell *shell);
int						is_quote(char *str);
char					*trimstartsp(char *str, int i);
void					my_putstr(char *str, t_shell **shell);
void					ft_free(t_shell *shell);
int						init_quote(char pattern, t_shell *shell);
int						del_key(char buffer[6], t_shell *shell);
t_shell					*init_shell(char **envp);
int						arrow_key(char buffer[6], t_shell *shell);
void					syncronize_line(t_shell *shell);
char					**ft_split_path(char *str);
t_shell					*read_file(t_shell *shell);
void					keydown(t_shell *shell);
void					keyup(t_shell *shell);
void					put_color(t_shell *shell);
void					keyhome(t_shell *shell);
void					keyend(t_shell *shell);
int						alpha_num(char buffer[3], t_shell *shell);
char					*addpos_line(char str, char *actu, int pos);
int						return_key(char buffer[3], t_shell *shell);
t_shell					*get_shell_struct(t_shell *shell);
void					ft_catchsign(void);
t_shell					*setup(char **environ);
void					term_error(int error, t_shell *shell);
void					init_terminal(t_shell *shell);
int						my_putchar(int c);
void					ft_clear(void);
void					ft_ul_video(char *str);
void					ft_ul(char *str);
void					ft_video(char *str);
int						term_back(struct termios term);
int						key_reader(t_shell *shell);
void					init_key_func(t_shell *shell);
int						print_pwd(t_shell *shell);
void					put_line(char *str, t_shell *shell);
void					clear_line(t_shell *shell);
void					clear_line2(t_shell *shell);
void					display_prompt(t_shell *shell);
void					del_inline(t_shell *shell);
void					setup_history(t_shell **shell);
void					add_history_command(char *command, \
						t_shell *shell, int i);
void					make_history_file(t_shell *shell);
t_shell					*history_up(t_shell *shell);
t_shell					*history_down(t_shell *shell);
void					signal_handler(int signo);

/*
**	sgalasso: globbing, expansions
*/

typedef struct s_match	t_match;
typedef struct s_gdata	t_gdata;

struct					s_match
{
	char		*name;
	t_match		*next;
};

struct					s_gdata
{
	char		*path;
	char		*new_line;
	t_match		*glob_lst;
	char		**samples;
	int			startslash;
	int			endslash;
	int			brac_error;
	int			brackets;
	int			braces;
	char		***case_tab;
	char		*case_str;
	char		**table;
};

int						ft_nb_joker(char *str);
int						ft_check_patern(char *patern, char *element, \
						int i, int j);
char					**ft_patern_split(char *str);
void					ft_new_line_data(char *word, t_gdata *gdata);
void					ft_glob_process(t_shell *shell);
char					*ft_expansion(char *line, t_shell *shell);
char					*ft_remove_mult(char *word);
int						ft_is_globchar(char c);
int						ft_is_metachar(char c);
void					ft_glob_loop(char **samples, t_gdata *gdata);
void					ft_glob_rec(char **samples, t_gdata *gdata);
int						ft_glob_brackets(char *str);
int						ft_glob_braces(char *str);
void					ft_tabdel(char **table);
t_match					*ft_find_match(char **samples, t_gdata *gdata);
void					ft_free_lst(t_match *match);
t_match					*ft_match_add(char *name, t_match *match_lst);
void					ft_case_tab(char *patern, t_gdata *gdata);
void					ft_case_str(char *patern, t_gdata *gdata);
int						ft_nbbrack(char *str);

/*
**	trponess: cd / env / setenv / unsetenv / echo
*/

void					ft_exit(const char *err_msg);
void					ft_echo(char **line);
char					**ft_cd(char **ev, char **line);
void					ft_env(char **line, char **ev);
char					**ft_set_un_env(char **line, char **ev);
char					**create_env(char **envp);
char					*get_env(char *name, char **envp);
int						xlook_for_envvar(char **ev, char *var);
char					*search_for_command(char *command, char *env_path);
void					ft_dmemdel(char ***arrptr);
char					**cd_flag(char **ev, char **line, char *flag_l);
int						is_dir(char *path);
int						is_link(char *path);
int						ft_error(char **line, int *flag, char **ev);
char					**ft_dup_env(char **ev);
char					**add_to_env(int pos, char **ev, char *envvar);
void					display_env(char **ev);
void					create_process(char **args, char **ev);
char					**remove_from_env(int pos, char **ev);
char					**obj_envp(char **new_envp);
int						list_size(t_token *z);
int						look_for_env_pos(char *str, char **env);
char					*get_env_value(char **env, char *env_val, int pos);
void					expansion_translator(t_token **list, char **ev);
char					*create_envvar(char *envvar, char *value);
char					**add_pwdvar_to_env(char *pwd_var, char **ev);
char					**change_paths(char **paths, char **ev, char flag);
char					*ft_getcwd(void);
int						is_dir(char *path);

#endif
