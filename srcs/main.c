/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:56:53 by lbegliom          #+#    #+#             */
/*   Updated: 2024/08/09 14:16:29 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_signal;

static int	rl_sighandler(void)
{
	return (0);
}

static int	start_prompt(t_minish *dt)
{
	dt->check->line_cmd = readline("minihell 😈 > ");
	if (!dt->check->line_cmd)
		return (printf("exit\n"), free_minish(dt), 0);
	if (ft_strlen(dt->check->line_cmd) > 0)
	{
		add_history(dt->check->line_cmd);
		if (parsing(dt) == 0)
		{
			ft_putstr_fd("minihell : Error syntax\n", 2);
			dt->status = 2;
		}
		else if (start_exec(dt) == 0)
			return (free_dt_elem(&dt->block_token), 1);
		if (dt->block_token)
			free_dt_elem(&dt->block_token);
		dt->block_token = NULL;
		free(dt->check->line_cmd);
	}
	return (1);
}

static void	check_signal(t_minish *dt)
{
	if (g_signal != 0)
	{
		dt->status = g_signal + 128;
		g_signal = 0;
	}
}

static int	start_minish(t_minish *dt)
{
	int	state;

	state = 1;
	while (state)
	{
		signal(SIGINT, &sig_handler_interactive);
		signal(SIGQUIT, SIG_IGN);
		check_signal(dt);
		rl_event_hook = rl_sighandler;
		state = start_prompt(dt);
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_minish	*dt_minish;

	(void)ac;
	(void)av;
	if (!envp || !envp[0])
		dt_minish = create_minish(NULL);
	else
		dt_minish = create_minish(envp);
	if (!dt_minish)
		return (1);
	return (start_minish(dt_minish));
}
