/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:41:23 by glions            #+#    #+#             */
/*   Updated: 2024/08/09 11:18:31 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_cmd *curr, t_minish *dt, t_cmd *head)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_putstr_fd("pwd: error retrieving current directory: getcwd:", 2);
		ft_putstr_fd(" cannot access parent directories: No such file", 2);
		ft_putstr_fd(" or directory\n", 2);
		if (head)
			(close_tab_pipes(head), free_cmd(head));
		else
			(close_tab_pipes(curr), free_cmd(curr));
		(free_minish(dt), exit(EXIT_FAILURE));
	}
	printf("%s\n", pwd);
	free(pwd);
}
