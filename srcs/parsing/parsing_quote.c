/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:53:04 by glions            #+#    #+#             */
/*   Updated: 2024/08/04 20:10:17 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*start_quote(t_dt_elem **token, char *value)
{
	t_dt_elem	*tmp;
	t_dt_elem	*next;

	tmp = *token;
	while (tmp && tmp->type != PIPE_LINE && !type_is_redir(tmp->type)
		&& tmp->type != WHITE_SPACE)
	{
		next = tmp->next;
		if (!type_is_quote(tmp->type))
		{
			value = ft_strjoin_w_free(value, tmp->value);
			if (!value)
				return (NULL);
		}
		if (!remove_dt_elem(token, &tmp))
			return (free(value), NULL);
		tmp = next;
	}
	return (value);
}

int	parsing_quote(t_dt_elem **tokens)
{
	t_dt_elem	*token;
	t_dt_elem	*tmp;

	token = *tokens;
	while (token)
	{
		while (token && type_is_quote(token->type))
		{
			tmp = token->next;
			if (!remove_dt_elem(tokens, &token))
				return (0);
			token = tmp;
		}
		if (token && token->type == WORD)
			token->value = start_quote(&token->next, token->value);
		if (token && !token->value)
			return (0);
		if (token)
			token = token->next;
	}
	return (1);
}
