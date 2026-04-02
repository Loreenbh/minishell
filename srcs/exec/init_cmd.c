/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 03:12:22 by glions            #+#    #+#             */
/*   Updated: 2024/08/05 10:54:28 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_list_cmd(t_cmd *list, t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = list;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = cmd;
}

static int	check_next_token(t_dt_elem **tokens, t_cmd **new_c)
{
	t_cmd	*cmd;

	while (*tokens && (*tokens)->type == PIPE_LINE)
	{
		*tokens = (*tokens)->next;
		cmd = create_cmd(tokens);
		if (!cmd)
			return (0);
		add_list_cmd(*new_c, cmd);
	}
	return (1);
}

int	init_cmd(t_dt_elem *tokens, t_cmd **new_c)
{
	*new_c = create_cmd(&tokens);
	if (!*new_c)
		return (0);
	if (!check_next_token(&tokens, new_c))
		return (free_cmd(*new_c), 0);
	return (1);
}
