/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_other_bltn.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 14:05:46 by glions            #+#    #+#             */
/*   Updated: 2024/08/09 12:14:11 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	copy_env(t_list_gl *env, int fd)
{
	t_list_gl	*curr;
	t_node_env	*curr_env;

	curr = env;
	while (curr)
	{
		curr_env = curr->content;
		write(fd, curr_env->name, ft_strlen(curr_env->name));
		if (curr_env->value)
		{
			write(fd, "=", 1);
			write(fd, curr_env->value, ft_strlen(curr_env->value));
		}
		write(fd, "\n", 1);
		curr = curr->next;
	}
	return (1);
}

int	other_built(t_cmd *curr, t_minish *dt, t_cmd *head)
{
	if (ft_strcmp(curr->tab_opt[0], "env") == 0)
	{
		print_env(dt->env_minish);
		(close_tab_pipes(curr), free_cmd(curr), free_minish(dt),
			exit(EXIT_SUCCESS));
	}
	else if (ft_strcmp(curr->tab_opt[0], "export") == 0)
	{
		if (!exec_export(curr, dt, head))
			return (0);
	}
	else if (ft_strcmp(curr->tab_opt[0], "unset") == 0)
	{
		if (!exec_unset(curr, dt, head))
			return (0);
	}
	else if (ft_strcmp(curr->tab_opt[0], "exit") == 0)
		if (!ft_exit(dt, curr, head))
			return (0);
	return (1);
}
