/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 11:40:09 by tblaudez          #+#    #+#             */
/*   Updated: 2018/12/15 20:48:38 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int	is_builtin(int type, char **args, char **envp)
{
	if (type == 0)
	{
		if (ft_strequ(args[0], "exit"))
			ft_exit("exit");
		else if (ft_strequ(args[0], "cd"))
			envp = ft_cd(envp, args);
		else if (ft_strequ(args[0], "setenv") || ft_strequ(args[0], "unsetenv"))
			envp = ft_set_un_env(args, envp);
		else
			return (0);
		obj_envp(envp);
		return (1);
	}
	else
	{
		if (ft_strequ(args[0], "env"))
			ft_env(args, envp);
		else if (ft_strequ(args[0], "echo"))
			ft_echo(args);
		else
			return (0);
		exit(EXIT_SUCCESS);
	}
}

static void	redirect_fds(t_redir *redir_list)
{
	int		fd;
	t_redir	*first_node;

	first_node = redir_list;
	while (redir_list)
	{
		if (redir_list->type == GRT)
			fd = open(redir_list->to, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (redir_list->type == D_GRT)
			fd = open(redir_list->to, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else if (redir_list->type == LSR)
			fd = open(redir_list->to, O_RDONLY);
		else if (redir_list->type == GRTAND || redir_list->type == LSRAND)
			fd = ft_atoi(redir_list->to);
		if (redir_list->type == GRTAND && ft_strequ("-", redir_list->to))
			close(ft_atoi(redir_list->from));
		else if (redir_list->type == LSRAND && ft_strequ("-", redir_list->from))
			close(ft_atoi(redir_list->to));
		else if (dup2(fd, ft_atoi(redir_list->from)) == -1)
			exit(EXIT_FAILURE);
		redir_list = redir_list->next;
	}
	close_all(first_node);
}

static void	execute_pipeline(int *input_fd, int pipefd[2], \
t_cmd *cmd_list, char **envp)
{
	pid_t	parent;

	if ((parent = fork()) == -1)
		ft_exit("21sh: fork error");
	else if (parent == 0)
	{
		if (*input_fd != 0)
		{
			if (dup2(*input_fd, 0) == -1)
				exit(EXIT_FAILURE);
			close(*input_fd);
		}
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		redirect_fds(cmd_list->redir);
		if (!is_builtin(1, cmd_list->args, envp))
			launch_binary(cmd_list->args, envp);
	}
	close(pipefd[1]);
	if (*input_fd)
		close(*input_fd);
	*input_fd = pipefd[0];
}

static int	execute_command(int input_fd, t_cmd *cmd_list, char **envp)
{
	pid_t	parent;

	if ((parent = fork()) == -1)
		ft_exit("21sh: fork error");
	else if (parent == 0)
	{
		if (input_fd != 0)
		{
			if (dup2(input_fd, 0) == -1)
				exit(EXIT_FAILURE);
			close(input_fd);
		}
		redirect_fds(cmd_list->redir);
		if (!is_builtin(1, cmd_list->args, envp))
			launch_binary(cmd_list->args, envp);
	}
	if (input_fd)
		close(input_fd);
	while (wait(&parent) >= 0)
		continue;
	return (parent);
}

void		shell_exec(t_cmd *cmd_list, char **envp)
{
	int		pipefd[2];
	int		input_fd;
	pid_t	pid;

	while (cmd_list)
	{
		pipefd[0] = -1;
		pipefd[1] = -1;
		input_fd = 0;
		envp = obj_envp(NULL);
		if (!cmd_list->args || is_builtin(0, cmd_list->args, envp))
		{
			cmd_list = cmd_list->next;
			continue ;
		}
		while (ft_is_in("pipe", cmd_list))
		{
			pipe(pipefd);
			execute_pipeline(&input_fd, pipefd, cmd_list, envp);
			cmd_list = cmd_list->next;
		}
		pid = execute_command(input_fd, cmd_list, envp);
		close(pipefd[1]);
		cmd_list = check_success(pid, cmd_list);
	}
}
