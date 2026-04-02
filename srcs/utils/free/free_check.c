/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 11:21:41 by lbegliom          #+#    #+#             */
/*   Updated: 2024/08/05 16:05:00 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_check(t_check *dt)
{
	if (dt)
	{
		if (dt->redirct)
			free(dt->redirct);
		if (dt->oprt)
			free(dt->oprt);
		if (dt->line_cmd)
			free(dt->line_cmd);
		if (dt->bltn)
			free(dt->bltn);
		free(dt);
	}
}
