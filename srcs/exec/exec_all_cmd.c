/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:41:45 by lbegliom          #+#    #+#             */
/*   Updated: 2024/08/08 18:31:02 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	close_process(t_cmd *cmd)
{
	if (!close_tmp_file(cmd))
		return (0);
	close_tab_pipes(cmd);
	return (1);
}

int	child_process1(t_cmd *cmd, t_minish *dt, t_cmd *head)
{
	int		n_redir[2];
	char	*path;
	char	**env;

	n_redir[1] = 0;
	n_redir[0] = 0;
	if (cmd->list_redirc)
		if (!get_redir(cmd, &n_redir[1], &n_redir[0]))
			return (1);
	if (n_redir[1] == 0)
		if (dup2(cmd->tab_pipes[cmd->id][1], STDOUT_FILENO) == -1)
			return (perror("dup2"), 1);
	if (!cmd->tab_opt[0])
		(close_tab_pipes(cmd), free_cmd(cmd), free_minish(dt), exit(0));
	path = get_path(cmd, dt, head);
	if (!path)
		return (ft_putstr_fd(cmd->tab_opt[0], 2),
			ft_putstr_fd(" : command not found\n", 2), 127);
	env = gen_env(dt->env_minish, NULL);
	if (!env || !close_process(cmd))
		return (1);
	if (execve(path, cmd->tab_opt, env) == -1)
		return (ft_split_free(env), free(path), perror("execve"), errno);
	return (1);
}

static int	redir_job(t_cmd *cmd, int n_redir[2])
{
	if (n_redir[0] == 0)
		if (dup2(cmd->tab_pipes[cmd->id - 1][0], STDIN_FILENO) == -1)
			return (perror("dup2"), 1);
	if (n_redir[1] == 0)
		if (dup2(cmd->tab_pipes[cmd->id][1], STDOUT_FILENO) == -1)
			return (perror("dup2"), 1);
	return (0);
}

int	child_process2(t_cmd *cmd, t_minish *dt, t_cmd *head)
{
	int		n_redir[2];
	char	*path;
	char	**env;

	n_redir[0] = 0;
	n_redir[1] = 0;
	if (cmd->list_redirc)
		if (!get_redir(cmd, &n_redir[1], &n_redir[0]))
			return (ft_putstr_fd("Error get redir\n", 2), 1);
	if (redir_job(cmd, n_redir))
		return (1);
	if (!cmd->tab_opt[0])
		(close_tab_pipes(cmd), free_cmd(cmd), free_minish(dt), exit(0));
	path = get_path(cmd, dt, head);
	if (!path)
		return (ft_putstr_fd(cmd->tab_opt[0], 2),
			ft_putstr_fd(" : CMD not found\n", 2), 127);
	env = gen_env(dt->env_minish, NULL);
	if (!env)
		return (ft_putstr_fd("Gen env failed\n", 2), 1);
	close_tab_pipes(cmd);
	if (execve(path, cmd->tab_opt, env) == -1)
		return (ft_split_free(env), free(path), perror("execve"), errno);
	return (1);
}

int	child_process3(t_cmd *cmd, t_minish *dt, t_cmd *head)
{
	int		n_redir[2];
	char	*path;
	char	**env;

	n_redir[0] = 0;
	n_redir[1] = 0;
	if (cmd->list_redirc)
		if (!get_redir(cmd, &n_redir[1], &n_redir[0]))
			return (1);
	if (n_redir[0] == 0)
		if (dup2(cmd->tab_pipes[cmd->id - 1][0], STDIN_FILENO) == -1)
			return (perror("dup2"), 1);
	if (!cmd->tab_opt[0])
		(close_tab_pipes(cmd), free_cmd(cmd), free_minish(dt), exit(0));
	path = get_path(cmd, dt, head);
	if (!path)
		return (ft_putstr_fd(cmd->tab_opt[0], 2),
			ft_putstr_fd(" : CMD not found\n", 2), 127);
	env = gen_env(dt->env_minish, NULL);
	if (!env)
		return (ft_putstr_fd("Gen env failed\n", 2), 1);
	close_tab_pipes(cmd);
	if (execve(path, cmd->tab_opt, env) == -1)
		return (ft_split_free(env), free(path), perror("execve"), errno);
	return (1);
}
