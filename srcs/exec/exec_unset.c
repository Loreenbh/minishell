/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbegliom <lbegliom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:37:59 by glions            #+#    #+#             */
/*   Updated: 2024/08/02 16:15:10 by lbegliom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_unset(t_cmd *curr, t_minish *dt, t_cmd *head)
{
	int	fd_env;
	int	i;

	i = 1;
	fd_env = open("a_supp", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_env == -1)
		return (0);
	while (curr->tab_opt && curr->tab_opt[i])
	{
		if (!ft_unset(&dt->env_minish, curr->tab_opt[i]))
			return (0);
		i++;
	}
	if (!copy_env(dt->env_minish, fd_env))
		return (0);
	close(fd_env);
	if (head)
		(close_tab_pipes(head), free_cmd(head));
	else
		free_cmd(curr);
	(free_minish(dt), exit(0));
}
