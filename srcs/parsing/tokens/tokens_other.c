/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_other.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 10:25:01 by glions            #+#    #+#             */
/*   Updated: 2024/08/05 16:25:27 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pars_env(char **value, char *str, t_minish *dt_minish, int *pos)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 1;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	tmp = ft_strndup(str + 1, i - 1);
	if (!tmp)
		return (0);
	tmp2 = ft_getenv(tmp, dt_minish->env_minish);
	if (!tmp2)
		return (free(tmp), 0);
	free(tmp);
	if (*value)
	{
		*value = ft_strjoin_w_free(*value, tmp2);
		free(tmp2);
		if (!*value)
			return (0);
	}
	else
		*value = tmp2;
	*pos += i;
	return (1);
}

static int	pars_status(char **value, t_minish *data_minish, int *pos)
{
	char	*tmp;

	tmp = ft_itoa(data_minish->status);
	if (!tmp)
		return (0);
	if (*value)
	{
		*value = ft_strjoin_w_free(*value, tmp);
		free(tmp);
		if (!*value)
			return (0);
	}
	else
		*value = tmp;
	*pos += 2;
	return (1);
}

static int	verif_break(char *str, t_minish *dt_minish, int i)
{
	return ((dt_minish->check->curr_state == GENERAL && (is_white(str[i])
				|| is_redir(str + i) || str[i] == '|' || str[i] == '\"'
				|| str[i] == '\''))
		|| (dt_minish->check->curr_state == IN_DQUOTE && str[i] == '\"')
		|| (dt_minish->check->curr_state == IN_QUOTE
			&& str[i] == '\''));
}

static int	while_job(char *str, int *i, t_minish *dt_minish, char **value)
{
	if ((dt_minish->check->curr_state == GENERAL
			|| dt_minish->check->curr_state == IN_DQUOTE) && str[*i] == '$'
		&& str[*i + 1] && (str[*i + 1] && (isalpha(str[*i + 1]) || str[*i
					+ 1] == '_')) && !dt_minish->check->here)
	{
		if (!pars_env(value, str + *i, dt_minish, i))
			return (0);
	}
	else if (str[*i] == '$' && str[*i + 1] && str[*i + 1] == '?'
		&& !dt_minish->check->here)
	{
		if (!pars_status(value, dt_minish, i))
			return (0);
	}
	else if (!pars_normal(value, str + *i, dt_minish, i))
		return (0);
	return (1);
}

int	token_word(char *str, t_dt_elem **token, t_minish *dt_minish, int *j)
{
	char	*value;
	int		i;

	value = NULL;
	i = 0;
	while (str[i])
	{
		if (verif_break(str, dt_minish, i))
			break ;
		if (!while_job(str, &i, dt_minish, &value))
			return (0);
		if (dt_minish->check->here == 2)
			dt_minish->check->here = 1;
	}
	*token = create_dt_elem(value, WORD, dt_minish->check->curr_state);
	if (!*token)
		return (free(value), 0);
	*j += i - 1;
	return (1);
}
