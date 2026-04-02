/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_syntax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbegliom <lbegliom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:48:57 by glions            #+#    #+#             */
/*   Updated: 2024/08/02 12:10:48 by lbegliom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parsing_quotes(int (*flag)[2], t_check *check, int i)
{
	if (check->line_cmd[i] == '\'' && !(*flag)[1])
	{
		check->nb_single++;
		if ((*flag)[0] == 1)
			(*flag)[0] = 0;
		else
			(*flag)[0] = 1;
	}
	else if (check->line_cmd[i] == '\"' && !(*flag)[0])
	{
		check->nb_double++;
		if ((*flag)[1] == 1)
			(*flag)[1] = 0;
		else
			(*flag)[1] = 1;
	}
	return (1);
}

int	parsing_syntax(t_check *check)
{
	int	i;
	int	flag[2];

	i = -1;
	flag[0] = 0;
	flag[1] = 0;
	while (check->line_cmd[++i])
		if (parsing_quotes(&flag, check, i) == 0)
			return (0);
	if ((check->nb_double != 0 && check->nb_double % 2 != 0)
		|| (check->nb_single != 0 && check->nb_single % 2 != 0))
		return (0);
	return (1);
}
