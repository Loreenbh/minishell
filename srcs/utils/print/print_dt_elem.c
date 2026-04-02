/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dt_elem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbegliom <lbegliom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:13:24 by glions            #+#    #+#             */
/*   Updated: 2024/08/02 14:39:29 by lbegliom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_dt_elem(t_dt_elem *elem)
{
	t_dt_elem	*tmp;
	int			i;

	if (!elem)
		printf("Le bloc n'a pas de token\n");
	tmp = elem;
	i = 0;
	while (tmp)
	{
		printf("[%d] -> [%s] [%d] [%d]\n", i, tmp->value, tmp->state,
			tmp->type);
		tmp = tmp->next;
		i++;
	}
}
