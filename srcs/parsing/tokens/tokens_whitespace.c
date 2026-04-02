/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_whitespace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 11:29:18 by glions            #+#    #+#             */
/*   Updated: 2024/07/31 11:35:19 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_whitespace(char *str, t_dt_elem **token, t_check *check, int j)
{
	enum e_type	type;

	if (check->curr_state == IN_DQUOTE || check->curr_state == IN_QUOTE)
		type = WORD;
	else
		type = WHITE_SPACE;
	*token = create_dt_elem(ft_strndup(str + j, 1), type, check->curr_state);
	if (!*token)
		return (0);
	return (1);
}
