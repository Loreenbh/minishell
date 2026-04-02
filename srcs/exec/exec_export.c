/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:41:48 by glions            #+#    #+#             */
/*   Updated: 2024/08/06 12:07:54 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_env_export(t_list_gl *env)
{
	char	*str;

	while (env)
	{
		str = ft_strjoin("export ", ((t_node_env *)env->content)->name);
		if (!str)
			return (0);
		if (((t_node_env *)env->content)->value)
		{
			str = ft_strjoin_w_free(str, "=\"");
			str = ft_strjoin_w_free(str, ((t_node_env *)env->content)->value);
			str = ft_strjoin_w_free(str, "\"");
			if (!str)
				return (0);
		}
		str = ft_strjoin_w_free(str, "\n");
		if (!str)
			return (0);
		(printf("%s", str), free(str));
		env = env->next;
	}
	return (1);
}

static int	accepted_char(char c, int mode)
{
	if (mode == 0)
		return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_'
			|| (c >= '0' && c <= '9') || c == '\0');
	else
		return (c != '=' && ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
				|| c == '_'));
}

static int	parsing_name(char *str)
{
	int	i;

	i = 1;
	if (!accepted_char(str[0], 1))
		return (0);
	while (str && str[i] && str[i] != '=')
	{
		if (!accepted_char(str[i], 0))
			return (0);
		i++;
	}
	if (str[i] == '\0')
		return (1);
	return (1);
}

static int	finish(t_cmd *curr, t_minish *dt, t_cmd *head, int var[2])
{
	if (!copy_env(dt->env_minish, var[0]))
		return (0);
	if (head)
		(close_tab_pipes(head), free_cmd(head));
	else
		free_cmd(curr);
	(close(var[0]), free_minish(dt), exit(var[1]));
	return (1);
}

int	exec_export(t_cmd *curr, t_minish *dt, t_cmd *head)
{
	int	var[2];

	if (curr->tab_opt && !curr->tab_opt[1])
	{
		if (!print_env_export(dt->env_minish))
			return (0);
		(close_tab_pipes(curr), free_cmd(curr), free_minish(dt), exit(0));
	}
	var[0] = open("a_supp", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (var[0] == -1)
		return (0);
	var[1] = 0;
	while (curr->tab_opt && curr->tab_opt[++var[1]])
	{
		if (!parsing_name(curr->tab_opt[var[1]]))
			return (ft_putstr_fd("minishell: export: '", 2),
				ft_putstr_fd(curr->tab_opt[var[1]], 2),
				ft_putstr_fd("' not a valid identifier\n", 2), finish(curr, dt,
					head, (int [2]){var[0], 1}));
		else if (!ft_export(curr->tab_opt[var[1]], &dt->env_minish))
			return (close(var[0]), 0);
	}
	if (!finish(curr, dt, head, (int [2]){var[0], 0}))
		return (0);
	return (1);
}
