/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:23:09 by glions            #+#    #+#             */
/*   Updated: 2024/08/09 12:23:28 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_var(char **pwd, char **old_pwd, char *save)
{
	char	*tmp;

	tmp = getcwd(NULL, 200);
	if (!tmp)
		return (0);
	*pwd = ft_strjoin("PWD=", tmp);
	if (!*pwd)
		return (free(tmp), 0);
	*old_pwd = ft_strjoin("OLDPWD=", save);
	if (!*old_pwd)
		return (free(*pwd), free(tmp), 0);
	free(tmp);
	return (1);
}
