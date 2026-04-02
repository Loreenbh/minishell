/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 14:06:58 by glions            #+#    #+#             */
/*   Updated: 2024/08/08 18:24:28 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_paths(t_list_gl *env, char ***path)
{
	char	*stock;

	if (!env)
		return (0);
	stock = ft_getenv("PATH", env);
	if (!stock)
		return (0);
	*path = ft_split(stock, ':');
	if (!*path)
		return (-1);
	free(stock);
	return (1);
}

char	*search_path_cmd(t_cmd *cmd, t_minish *dt)
{
	int		i;
	char	*tmp;
	char	**path;

	i = 0;
	tmp = NULL;
	if (cmd->tab_opt[0][0] == '/' || !ft_strncmp(cmd->tab_opt[0], "./", 2))
		return (ft_strdup(cmd->tab_opt[0]));
	if (!init_paths(dt->env_minish, &path))
		return (NULL);
	while (path && path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		if (!tmp)
			return (ft_split_free(path), NULL);
		tmp = ft_strjoin_w_free(tmp, cmd->tab_opt[0]);
		if (!tmp)
			return (ft_split_free(path), NULL);
		if (access(tmp, F_OK | X_OK) == 0)
			return (ft_split_free(path), tmp);
		free(tmp);
		i++;
	}
	ft_split_free(path);
	return (NULL);
}

char	*exec_builtin(t_cmd *cmd, t_minish *dt, t_cmd *head)
{
	char	*exec_name;

	exec_name = NULL;
	exec_name = search_path_built(cmd, exec_name, dt, head);
	if (!exec_name)
		return (NULL);
	if (access(exec_name, F_OK | X_OK) == 0)
		return (exec_name);
	return (NULL);
}

int	check_if_builtin(char **bltn, t_cmd *curr)
{
	int	i;
	int	j;

	i = 0;
	while (bltn && bltn[i])
	{
		j = 0;
		while (curr->tab_opt && curr->tab_opt[j])
		{
			if (ft_strcmp(curr->tab_opt[j], bltn[i]) == 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

char	*get_path(t_cmd *cmd, t_minish *dt, t_cmd *head)
{
	char	*path_built;

	path_built = NULL;
	if (check_if_builtin(dt->check->bltn, cmd))
	{
		path_built = exec_builtin(cmd, dt, head);
		if (!path_built)
			return (NULL);
		return (path_built);
	}
	else
	{
		path_built = search_path_cmd(cmd, dt);
		if (!path_built)
			return (NULL);
		return (path_built);
	}
	return (NULL);
}
