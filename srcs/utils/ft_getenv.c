/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:49:39 by lbegliom          #+#    #+#             */
/*   Updated: 2024/08/08 16:53:03 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *name, t_list_gl *env)
{
	char	*value;

	while (env)
	{
		if (!ft_strcmp(name, ((t_node_env *)env->content)->name))
		{
			value = ft_strdup(((t_node_env *)env->content)->value);
			if (!value)
				return (NULL);
			return (value);
		}
		env = env->next;
	}
	return (ft_strdup(""));
}
