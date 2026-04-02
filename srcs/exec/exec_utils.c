/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbegliom <lbegliom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 09:51:28 by lbegliom          #+#    #+#             */
/*   Updated: 2024/08/02 15:36:17 by lbegliom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_redirc(t_redir *list)
{
	int	i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

int	count_pipe(t_cmd *cmd, int *n_pipe)
{
	t_cmd	*curr;

	curr = cmd;
	while (curr)
	{
		if (curr->next)
			(*n_pipe)++;
		curr = curr->next;
	}
	return (*n_pipe);
}

int	nb_cmd(t_cmd *cmd)
{
	int		size;
	t_cmd	*curr;

	size = 0;
	curr = cmd;
	while (curr)
	{
		size++;
		curr = curr->next;
	}
	return (size);
}

int	init_tab_fd(t_cmd *curr_cmd)
{
	int	n_redirc;
	int	i;

	i = 0;
	n_redirc = count_redirc(curr_cmd->list_redirc);
	curr_cmd->tab_fd = malloc(sizeof(int *) * n_redirc);
	if (!curr_cmd->tab_fd)
		return (0);
	while (i < n_redirc)
	{
		curr_cmd->tab_fd[i] = malloc(sizeof(int));
		if (!curr_cmd->tab_fd[i])
			return (0);
		i++;
	}
	return (1);
}

int	init_tab_pipes(int n_pipe, int ***tab)
{
	int	i;

	*tab = malloc(sizeof(int *) * n_pipe);
	if (!*tab)
		return (1);
	i = -1;
	while (++i < n_pipe)
		(*tab)[i] = NULL;
	i = -1;
	while (++i < n_pipe)
	{
		(*tab)[i] = malloc(sizeof(int) * 2);
		if (!(*tab)[i])
			return (1);
		if (pipe((*tab)[i]) == -1)
		{
			free((*tab)[i]);
			(*tab)[i] = NULL;
			return (perror("pipe"), errno);
		}
	}
	return (0);
}
