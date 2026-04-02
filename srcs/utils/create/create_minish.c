/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_minish.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 11:03:45 by lbegliom          #+#    #+#             */
/*   Updated: 2024/08/05 16:16:42 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_path_echo(t_minish *dt)
{
	char	buff[100];

	dt->path_echo = getcwd(buff, 100);
	if (!dt->path_echo)
		return (0);
	dt->path_echo = ft_strjoin(dt->path_echo, "/ft_echo");
	if (!dt->path_echo)
		return (0);
	return (1);
}

t_minish	*create_minish(char **envp)
{
	t_minish	*new;
	int			i;
	int			m;

	new = malloc(sizeof(t_minish));
	if (!new)
		return (NULL);
	new->block_token = NULL;
	new->env_minish = NULL;
	m = 0;
	if (envp)
		m = 1;
	i = -1;
	while (m && envp[++i])
		ft_export(envp[i], &new->env_minish);
	if (m && !new->env_minish)
		return (free(new), NULL);
	new->status = 0;
	new->flag_env = 0;
	if (!set_path_echo(new))
		return (free(new), NULL);
	new->check = create_check();
	if (!new->check)
		return (free(new), NULL);
	return (new);
}
