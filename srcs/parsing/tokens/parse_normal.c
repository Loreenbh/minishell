/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_normal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 11:20:09 by glions            #+#    #+#             */
/*   Updated: 2024/07/31 15:01:02 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	verif_cond(char *str, int i, t_minish *dt_minish)
{
	return (str[i] && ((dt_minish->check->curr_state == GENERAL
				&& (!is_white(str[i]) && (str[i] != '$' || i == 0)
					&& !is_redir(str + i) && str[i] != '|' && str[i] != '\"'
					&& str[i] != '\''))
			|| (dt_minish->check->curr_state == IN_DQUOTE
				&& (str[i] != '$' || i == 0) && str[i] != '\"')
			|| (dt_minish->check->curr_state == IN_QUOTE
				&& str[i] != '\'')));
}

int	pars_normal(char **value, char *str, t_minish *dt_minish, int *pos)
{
	char	*tmp;
	int		i;

	i = 0;
	while (verif_cond(str, i, dt_minish))
		i++;
	tmp = ft_strndup(str, i);
	if (!tmp)
		return (0);
	if (*value)
	{
		*value = ft_strjoin_w_free(*value, tmp);
		free(tmp);
		if (!*value)
			return (0);
	}
	else
		*value = tmp;
	*pos += i;
	return (1);
}
