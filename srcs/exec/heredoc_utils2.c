/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:23:13 by lbegliom          #+#    #+#             */
/*   Updated: 2024/08/09 12:52:42 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	close_tmp_file(t_cmd *cmd)
{
	t_redir	*redir;
	t_cmd	*curr;
	int		i;

	i = 0;
	curr = cmd;
	while (curr)
	{
		redir = curr->list_redirc;
		while (redir)
		{
			if (redir->type == HERE_DOC_IN && redir->name_heredoc)
			{
				if (unlink(redir->name_heredoc) == -1)
					return (0);
				i++;
			}
			redir = redir->next;
		}
		curr = curr->next;
	}
	return (1);
}

static char	*get_dollar(char *str, int *i, t_minish *dt)
{
	char	*name;
	char	*value;
	int		k;

	k = 0;
	while (str[k] && (ft_isalnum(str[k]) || str[k] == '_'))
		k++;
	name = ft_strndup(str, k);
	if (!name)
		return (NULL);
	*i += k + 1;
	value = ft_getenv(name, dt->env_minish);
	if (!value)
		return (NULL);
	free(name);
	return (value);
}

static int	check_dollar(char *str, char **value, int *i, t_minish *dt)
{
	char	*tmp;

	tmp = get_dollar(str + *i + 1, i, dt);
	if (!tmp)
	{
		if (*value)
			free(*value);
		return (0);
	}
	if (!*value)
		*value = tmp;
	else
	{
		*value = ft_strjoin_w_free(*value, tmp);
		free(tmp);
		if (!*value)
			return (0);
	}
	return (1);
}

static int	add_char(char *str, char **value, int *i)
{
	char	*tmp;

	tmp = ft_strndup(str + *i, 1);
	if (!tmp)
	{
		if (*value)
			free(*value);
		return (0);
	}
	if (!*value)
		*value = tmp;
	else
	{
		*value = ft_strjoin_w_free(*value, tmp);
		free(tmp);
		if (!*value)
			return (0);
	}
	return (1);
}

char	*convert_to_value(char *str, t_minish *dt)
{
	int		i;
	char	*value;

	value = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && (ft_isalpha(str[i + 1]) || str[i
					+ 1] == '_'))
		{
			if (!check_dollar(str, &value, &i, dt))
				return (NULL);
		}
		else
		{
			if (!add_char(str, &value, &i))
				return (NULL);
			i++;
		}
	}
	return (value);
}
