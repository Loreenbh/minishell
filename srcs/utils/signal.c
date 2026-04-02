/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 10:51:51 by glions            #+#    #+#             */
/*   Updated: 2024/08/09 14:16:22 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal;

void	sig_handler_interactive(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		rl_done = 1;
		g_signal = SIGINT;
	}
}

void	sig_handler_non_interactive(int signum)
{
	if (signum == SIGINT)
	{
		write(2, "\n", 1);
		g_signal = SIGINT;
	}
	else if (signum == SIGQUIT)
	{
		write(2, "Quit (core dumped)\n", 19);
		g_signal = SIGQUIT;
	}
}

void	sig_handler_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		write(2, "^C", 2);
		g_signal = SIGINT;
	}
}
