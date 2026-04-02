/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbegliom <lbegliom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:11:45 by glions            #+#    #+#             */
/*   Updated: 2024/08/02 15:04:17 by lbegliom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_redir(t_cmd *cmd)
{
	int	i;

	printf("tab_pipes:\n");
	i = 0;
	while (i < cmd->utils.n_pipe)
	{
		printf("pipe[%d]->%d;%d\n", i, cmd->tab_pipes[i][0],
			cmd->tab_pipes[i][1]);
		i++;
	}
}

void	print_cmd(t_cmd *cmd, int mode)
{
	t_redir	*redir;
	int		i;

	if (cmd)
	{
		redir = cmd->list_redirc;
		if (!redir)
			printf("Ne possede pas de redirection\n");
		while (redir)
		{
			printf("Type: %d, File: %s\n", redir->type, redir->name_file);
			if (redir->name_heredoc)
				printf("name_heredoc->%s\n", redir->name_heredoc);
			redir = redir->next;
		}
		i = -1;
		while (cmd->tab_opt[++i])
			printf("opt : %s\n", cmd->tab_opt[i]);
		if (cmd->tab_pipes)
			print_redir(cmd);
		printf("pid->%d ; status->%d\n", cmd->pid, cmd->status);
		printf("\n");
		if (cmd->next && mode)
			print_cmd(cmd->next, 1);
	}
}
