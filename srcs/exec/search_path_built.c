/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path_built.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 14:18:02 by glions            #+#    #+#             */
/*   Updated: 2024/08/09 14:16:55 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	do_cd(t_cmd *curr, t_minish *dt, t_cmd *head)
{
	if (ft_strcmp(curr->tab_opt[0], "cd") == 0)
	{
		if (change_dir(curr, dt, 0))
			(close_tab_pipes(head), free_cmd(head), free_minish(dt), exit(1));
		(close_tab_pipes(head), free_cmd(head), free_minish(dt),
			exit(EXIT_SUCCESS));
	}
	return (1);
}

static int	verif_pwd(t_cmd *curr)
{
	int	i;

	i = -1;
	while (curr->tab_opt[++i])
		if (curr->tab_opt[i][0] == '-')
			return (ft_putstr_fd("pwd: option not allowed\n", 2), 0);
	return (1);
}

static void	clean_pwd(t_cmd *curr, t_cmd *head, t_minish *dt, int status)
{
	if (curr->utils.n_pipe > 0)
		close_tab_pipes(head);
	if (!head)
		free_cmd(curr);
	else
		free_cmd(head);
	(free_minish(dt), exit(status));
}

char	*search_path_built(t_cmd *curr, char *exec, t_minish *dt, t_cmd *head)
{
	if (ft_strcmp(curr->tab_opt[0], "echo") == 0)
	{
		exec = dt->path_echo;
		return (exec);
	}
	else if (ft_strcmp(curr->tab_opt[0], "pwd") == 0)
	{
		if (!verif_pwd(curr))
			clean_pwd(curr, head, dt, 2);
		ft_pwd(curr, dt, head);
		clean_pwd(curr, head, dt, 0);
	}
	else if (ft_strcmp(curr->tab_opt[0], "cd") == 0)
	{
		if (!do_cd(curr, dt, head))
			return (0);
	}
	else if (!other_built(curr, dt, head))
		return (NULL);
	return (NULL);
}
