/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:26:46 by glions            #+#    #+#             */
/*   Updated: 2024/08/09 14:12:50 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_swap(char *pwd, char *old, t_minish *dt)
{
	char	*tmp_old;
	char	*tmp;

	if (!pwd || !old)
	{
		if (pwd)
			free(pwd);
		if (old)
			free(old);
		return (1);
	}
	tmp_old = old;
	tmp = ft_strjoin("OLDPWD=", pwd);
	if (!tmp)
		return (free(pwd), free(old), 1);
	if (!ft_export(tmp, &dt->env_minish))
		return (free(pwd), free(old), free(tmp), 1);
	free(tmp);
	tmp = ft_strjoin("PWD=", old);
	if (!tmp)
		return (free(pwd), free(old), 1);
	if (!ft_export(tmp, &dt->env_minish))
		return (free(pwd), free(old), free(tmp), 1);
	(printf("%s\n", pwd), free(pwd), free(old), free(tmp));
	return (0);
}

int	ft_cd(const char *path, t_minish *dt)
{
	if (ft_strcmp((char *)path, "-") == 0)
	{
		return (ft_swap(ft_getenv("PWD", dt->env_minish), ft_getenv("OLDPWD",
					dt->env_minish), dt));
	}
	else if (chdir(path) == -1)
	{
		ft_putstr_fd("minihell : cd : ", 2);
		ft_putstr_fd((char *)path, 2);
		ft_putstr_fd(" No such file or directory\n", 2);
		return (errno);
	}
	return (0);
}
