/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_dt_elem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbegliom <lbegliom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:41:12 by lbegliom          #+#    #+#             */
/*   Updated: 2024/08/02 14:42:29 by lbegliom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	remove_dt_elem(t_dt_elem **list, t_dt_elem **elem)
{
	t_dt_elem	*tmp;
	t_dt_elem	*before;

	tmp = *list;
	if (*list == *elem)
	{
		tmp = (*list)->next;
		(free((*list)->value), free(*list));
		*list = tmp;
		return (1);
	}
	while (tmp)
	{
		if (tmp == *elem)
		{
			before->next = tmp->next;
			(free(tmp->value), free(tmp));
			return (1);
		}
		before = tmp;
		tmp = tmp->next;
	}
	return (0);
}

void	free_dt_elem(t_dt_elem **elem)
{
	t_dt_elem	*dt;
	t_dt_elem	*tmp;

	dt = *elem;
	while (dt)
	{
		tmp = dt->next;
		if (dt->value)
		{
			free(dt->value);
			dt->value = NULL;
		}
		free(dt);
		dt = tmp;
	}
}
