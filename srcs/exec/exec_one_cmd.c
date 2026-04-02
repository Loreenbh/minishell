/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:35:54 by lbegliom          #+#    #+#             */
/*   Updated: 2024/08/09 12:27:37 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	modif_env(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->tab_opt && cmd->tab_opt[i])
	{
		if (((ft_strcmp(cmd->tab_opt[i], "export") == 0)
				|| (ft_strcmp(cmd->tab_opt[i], "unset") == 0)) && cmd->tab_opt[i
				+ 1])
			return (1);
		i++;
	}
	return (0);
}

static int	last_job(t_cmd *cmd, t_minish *dt)
{
	int	status;

	cmd->pid = fork();
	if (cmd->pid == -1)
		return (perror("fork"), 0);
	else if (cmd->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		status = one_child(cmd, dt);
		(free_cmd(cmd), free_minish(dt), exit(status));
	}
	else
	{
		waitpid(cmd->pid, &status, 0);
		if (WIFEXITED(status))
			dt->status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			dt->status = WTERMSIG(status);
		if (!parent_task(dt))
			return (0);
	}
	return (1);
}

int	exec_simple_cmd(t_cmd *cmd, t_minish *dt)
{
	int	heredoc;

	heredoc = check_if_heredoc(cmd);
	if (heredoc != 0)
		if (!exec_heredoc(cmd, dt))
			return (0);
	if (!cmd->tab_opt)
		return (1);
	if (ft_strcmp(cmd->tab_opt[0], "cd") == 0)
	{
		dt->status = change_dir(cmd, dt, 1);
		return (1);
	}
	else if (ft_strcmp(cmd->tab_opt[0], "exit") == 0)
	{
		if (!ft_exit(dt, cmd, cmd))
			return (0);
		dt->status = 1;
		return (1);
	}
	dt->flag_env = modif_env(cmd);
	if (!last_job(cmd, dt))
		return (0);
	return (1);
}
