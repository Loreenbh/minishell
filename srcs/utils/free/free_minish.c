/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minish.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 11:20:58 by lbegliom          #+#    #+#             */
/*   Updated: 2024/08/05 10:51:26 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_node_env(void *env)
{
	t_node_env	*el;

	el = env;
	if (el)
	{
		if (el->name)
			free(el->name);
		if (el->value)
			free(el->value);
		free(el);
		el = NULL;
	}
}

void	free_minish(t_minish *dt)
{
	if (dt)
	{
		if (dt->env_minish)
			free_list_gl(&dt->env_minish, &free_node_env);
		if (dt->block_token)
			free_dt_elem(&dt->block_token);
		if (dt->check)
			free_check(dt->check);
		if (dt->path_echo)
			free(dt->path_echo);
		free(dt);
	}
}
