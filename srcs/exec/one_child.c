/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_child.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:35:40 by glions            #+#    #+#             */
/*   Updated: 2024/08/09 11:06:54 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_all_redir_out(int **fd, t_redir *redir, int i)
{
	if (redir->type == REDIR_OUT || redir->type == HERE_DOC_OUT)
	{
		if (redir->type == REDIR_OUT)
			*fd[i] = open(redir->name_file, O_CREAT | O_TRUNC | O_WRONLY, 0777);
		else
			*fd[i] = open(redir->name_file, O_CREAT | O_APPEND | O_WRONLY,
					0777);
		if (*fd[i] == -1)
			return (perror("minihell"), 0);
		if (dup2(*fd[i], STDOUT_FILENO) == -1)
			return (0);
		close(*fd[i]);
	}
	return (1);
}

int	get_all_redir(int **fd, t_redir *redir, int i)
{
	if (redir->type == REDIR_IN)
	{
		*fd[i] = open(redir->name_file, O_RDONLY);
		if (*fd[i] == -1)
			return (perror("minihell"), 0);
		if (dup2(*fd[i], STDIN_FILENO) == -1)
			return (0);
		close(*fd[i]);
	}
	else if (redir->type == HERE_DOC_IN)
	{
		*fd[i] = open(redir->name_heredoc, O_RDONLY);
		if (*fd[i] == -1)
			return (perror("minihell"), 0);
		if (dup2(*fd[i], STDIN_FILENO) == -1)
			return (0);
		close(*fd[i]);
	}
	else if (redir->type == REDIR_OUT || redir->type == HERE_DOC_OUT)
		if (!get_all_redir_out(fd, redir, i))
			return (0);
	return (1);
}

static int	exist(char *path)
{
	if (access(path, F_OK) == -1)
		return (0);
	return (1);
}

static int	do_exec(t_cmd *cmd, t_minish *dt)
{
	char	*path;
	char	**env;

	path = get_path(cmd, dt, NULL);
	if (!path || !exist(path))
	{
		if (path)
			free(path);
		return (ft_putstr_fd(cmd->tab_opt[cmd->pos_cmd], 2),
			ft_putstr_fd(": command not found\n", 2), 127);
	}
	env = gen_env(dt->env_minish, NULL);
	if (!env)
		return (ft_putstr_fd("Gen env failed\n", 2), 1);
	if (execve(path, cmd->tab_opt, (char *const *)env) == -1)
		return (free(path), ft_split_free(env), perror("execve"), 126);
	return (1);
}

int	one_child(t_cmd *cmd, t_minish *dt)
{
	t_redir	*redir;
	int		i;

	i = 0;
	if (!init_tab_fd(cmd))
		return (1);
	redir = cmd->list_redirc;
	while (redir)
	{
		if (!get_all_redir(cmd->tab_fd, redir, i))
			return (free_fd(cmd), 1);
		redir = redir->next;
		i++;
	}
	if (!close_tmp_file(cmd))
		return (1);
	if (!cmd->tab_opt[0])
		(close_tab_pipes(cmd), free_cmd(cmd), free_minish(dt),
			exit(EXIT_SUCCESS));
	return (do_exec(cmd, dt));
}
