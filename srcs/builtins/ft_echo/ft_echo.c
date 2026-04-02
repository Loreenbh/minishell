/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:45:33 by glions            #+#    #+#             */
/*   Updated: 2024/08/08 16:50:25 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_option(char *str, int *not_line)
{
	int	i;

	if (str[0] != '-')
		return (0);
	i = 0;
	while (str && str[++i])
		if (str[i] != 'n')
			return (0);
	if (not_line)
		*not_line = 1;
	return (1);
}

static void	print_str(char **tab, int *i, int *k)
{
	int	j;

	j = -1;
	while (tab && tab[*i][++j])
		write(1, &tab[*i][j], 1);
	*i += 1;
	if (tab[*i] != NULL)
		write(1, " ", 1);
	*k = 1;
}

int	ft_echo(char **tab)
{
	int	i;
	int	not_line;
	int	k;

	i = 0;
	k = 0;
	not_line = 0;
	while (tab && tab[i])
	{
		if (k == 0 && i == 0 && is_option(tab[i], &not_line))
			i++;
		else if (k == 0 && is_option(tab[i], NULL))
			i++;
		else
			print_str(tab, &i, &k);
	}
	if (!not_line)
		printf("\n");
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	(void)envp;
	if (ac <= 1)
		printf("\n");
	ft_echo(av + 1);
	return (0);
}
