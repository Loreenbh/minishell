/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 11:06:52 by lbegliom          #+#    #+#             */
/*   Updated: 2024/08/09 14:12:02 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_value(char **tab, t_node_env *env)
{
	free(tab[0]);
	free(env->value);
	env->value = tab[1];
}

int	update_env(t_list_gl **list, char **tab)
{
	t_list_gl	*curr;
	t_node_env	*node_env;

	curr = *list;
	while (curr != NULL)
	{
		node_env = curr->content;
		if (ft_strcmp(tab[0], node_env->name) == 0)
			break ;
		curr = curr->next;
	}
	if (curr == NULL)
	{
		node_env = malloc(sizeof(t_node_env));
		if (!node_env)
			return (0);
		node_env->name = tab[0];
		node_env->value = tab[1];
		if (addback_list_gl(list, new_element_gl(node_env)) == 0)
			return (free(node_env), 0);
	}
	else
		update_value(tab, node_env);
	return (1);
}

static int	do_while(char ***tab, int i, char *str)
{
	if (str[i + 1] == '\0')
	{
		*tab = malloc(sizeof(char *));
		if (!*tab)
			return (0);
		(*tab)[0] = NULL;
		return (1);
	}
	return (2);
}

char	**split_env(char *str, char c)
{
	int		i;
	char	**tab;
	int		e;

	if (!str)
		return (NULL);
	i = -1;
	while (str[++i] && str[i] != c)
	{
		e = do_while(&tab, i, str);
		if (e == 0)
			return (0);
		else if (e == 1)
			return (tab);
	}
	tab = malloc(2 * sizeof(char *));
	if (!tab)
		return (NULL);
	tab[0] = ft_strndup(str, i);
	if (!tab[0])
		return (free(tab), NULL);
	tab[1] = ft_strndup(str + i + 1, ft_strlen(str + i + 1));
	if (!tab[1])
		return (free(tab[0]), free(tab), NULL);
	return (tab);
}

int	ft_export(char *str, t_list_gl **list)
{
	char	**tab;

	tab = split_env(str, '=');
	if (!tab)
		return (0);
	else if (!tab[0])
	{
		free(tab);
		tab = malloc(2 * sizeof(char *));
		if (!tab)
			return (0);
		tab[0] = ft_strdup(str);
		tab[1] = NULL;
	}
	if (update_env(list, tab) == 0)
		return (ft_split_free(tab), 0);
	return (free(tab), 1);
}
