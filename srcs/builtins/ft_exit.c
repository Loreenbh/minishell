/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:40:27 by glions            #+#    #+#             */
/*   Updated: 2024/08/09 12:20:06 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long int	ft_atoll(char *str)
{
	int					i;
	int					sign;
	long long			res;
	unsigned long long	number;

	i = 0;
	number = 0;
	while (str[i] == '0')
		i++;
	if (str[i] == '+')
		i++;
	sign = (str[i] == '-');
	i += sign;
	while (str[i] != '\0')
		number = number * 10 + str[i++] - '0';
	if (sign == 1)
		res = (long long int)(-1 * number);
	else
		res = (long long int)number;
	return (res);
}

int	ft_strnum(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	number_too_big(char *str)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (str[i] == '0')
		i++;
	len = ft_strlen(str) - i;
	if (str[i] == '-')
	{
		if (len > 20)
			return (0);
		if (len == 20 && ft_strcmp(&str[i], "-9223372036854775808") > 0)
			return (0);
	}
	else
	{
		if (len > 19)
			return (0);
		if (len == 19 && ft_strcmp(&str[i], "9223372036854775807") > 0)
			return (0);
	}
	return (1);
}

int	exit_code_exit(char *str)
{
	long long	number;

	number = ft_atoll(str);
	if (number >= 0)
		return ((int)(number % 256));
	number = number % 256;
	return ((int)((number + 256) % 256));
}

int	ft_exit(t_minish *dt, t_cmd *cmd, t_cmd *head)
{
	char	**arg;
	int		exit_code;

	arg = cmd->tab_opt;
	printf("exit\n");
	if (arg[1] == NULL)
		exit_code = dt->status;
	else if (ft_strnum(arg[1]) == 0 || number_too_big(arg[1]) == 0)
	{
		(write(2, "exit :", 6), write(2, arg[1], ft_strlen(arg[1])), write(2,
				": numeric argument required\n", 28));
		exit_code = 2;
	}
	else if (arg[2] != NULL)
	{
		write(2, "exit: too many arguments\n", 25);
		exit_code = 1;
		return (1);
	}
	else
		exit_code = exit_code_exit(arg[1]);
	(close_tab_pipes(head), free_cmd(head), free_minish(dt), exit(exit_code));
}
