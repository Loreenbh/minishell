/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:51:29 by glions            #+#    #+#             */
/*   Updated: 2024/08/09 12:29:28 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal;

static void	wait_all_cmd(t_cmd *cmd, t_minish *dt_minish)
{
	while (cmd)
	{
		waitpid(cmd->pid, &dt_minish->status, 0);
		if (WIFEXITED(dt_minish->status))
			dt_minish->status = WEXITSTATUS(dt_minish->status);
		else if (WIFSIGNALED(dt_minish->status))
			dt_minish->status = WTERMSIG(dt_minish->status);
		cmd = cmd->next;
	}
}

int	start_exec(t_minish *dt_minish)
{
	t_cmd		*cmd;
	t_cmd		*head;
	int			e;

	if (!init_cmd(dt_minish->block_token, &cmd))
		return (0);
	e = exec_cmd(cmd, dt_minish);
	if (e == -1)
		return (free_cmd(cmd), -1);
	else if (!e)
		return (free_cmd(cmd), 0);
	head = cmd;
	if (cmd->utils.n_pipe > 0)
		close_tab_pipes(cmd);
	wait_all_cmd(cmd, dt_minish);
	if (dt_minish->status == 0)
		g_signal = 0;
	free_cmd(head);
	return (1);
}
