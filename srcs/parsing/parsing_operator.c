/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_operator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:37:51 by glions            #+#    #+#             */
/*   Updated: 2024/08/05 16:24:38 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_operator(char *str, t_check *check, t_dt_elem **curr_block)
{
	t_dt_elem	*el;

	el = NULL;
	if (ft_strncmp(str, "|", 1) == 0 && check->curr_state == GENERAL)
	{
		el = create_dt_elem(ft_strdup("|"), PIPE_LINE, check->curr_state);
		if (!el)
			return (0);
	}
	if (el)
	{
		if (add_back_elem(curr_block, el) == 0)
			return (free(el), 0);
		return (1);
		check->here = 0;
	}
	return (-1);
}

int	is_operator(char *str)
{
	if (ft_strncmp(str, "|", 1) == 0)
		return (1);
	return (0);
}
