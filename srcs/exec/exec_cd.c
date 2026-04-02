/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 14:57:15 by glions            #+#    #+#             */
/*   Updated: 2024/08/09 14:11:39 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	no_option(char **tmp, t_minish *dt)
{
	*tmp = ft_getenv("HOME", dt->env_minish);
	if (!*tmp)
		return (0);
	if (ft_cd(*tmp, NULL) != 0)
		return (free(*tmp), 0);
	return (1);
}

static int	do_job(char **tmp, t_cmd *cmd)
{
	char	buff[1000];

	*tmp = ft_strjoin(getcwd(buff, 1000), "/");
	if (!*tmp)
		return (1);
	*tmp = ft_strjoin_w_free(*tmp, cmd->tab_opt[1]);
	if (!*tmp)
		return (free(*tmp), 1);
	if (ft_cd(*tmp, NULL) != 0)
		return (free(*tmp), 1);
	return (0);
}

static int	change_env(char *tmp, char *save, t_minish *dt)
{
	char	*pwd;
	char	*old_pwd;

	pwd = NULL;
	old_pwd = NULL;
	if (!update_var(&pwd, &old_pwd, save))
		return (free(tmp), 0);
	if (!ft_export(pwd, &dt->env_minish))
		return (free(pwd), free(old_pwd), free(tmp), 0);
	if (!ft_export(old_pwd, &dt->env_minish))
		return (free(pwd), free(old_pwd), free(tmp), 0);
	return (free(pwd), free(old_pwd), 1);
}

static int	change_dir2(char **tmp, t_cmd *cmd, t_minish *dt, int *change)
{
	if (!cmd->tab_opt[1])
	{
		if (!no_option(tmp, dt))
			return (1);
	}
	else if (ft_strcmp(cmd->tab_opt[1], "-") == 0)
	{
		*change = 0;
		return (ft_cd(cmd->tab_opt[1], dt));
	}
	else if (cmd->tab_opt[1] && cmd->tab_opt[1][0] != '/')
	{
		if (do_job(tmp, cmd))
			return (1);
	}
	else if (ft_cd(cmd->tab_opt[1], NULL) != 0)
		return (1);
	return (0);
}

int	change_dir(t_cmd *cmd, t_minish *dt, int change)
{
	char	*tmp;
	char	buff[1000];
	char	*save;

	tmp = NULL;
	save = getcwd(buff, 1000);
	if (cmd->tab_opt[1] && cmd->tab_opt[2])
		return (ft_putstr_fd("minihell: cd: too many arguments\n", 2), 1);
	if (!save && cmd->tab_opt[1] && !ft_strncmp(cmd->tab_opt[1], ".", 1))
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(cmd->tab_opt[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	if (change_dir2(&tmp, cmd, dt, &change))
		return (1);
	if (change == 1)
		if (!change_env(tmp, save, dt))
			return (1);
	if (tmp)
		free(tmp);
	return (0);
}
