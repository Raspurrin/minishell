/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 22:46:32 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/03 02:46:15 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	path_innit(t_data *data)
{
	t_env	*lst;

	lst = find_node(data->envp_head, "PATH");
	data->paths = ft_split(lst->value, ':');
	return ;
}

/**
 * example: str: "something=blue" del: '='
 * split[0] = something;
 * split[1] = blue;
 * split[2] = NULL;
 * str: "something" del: '-'
 * split[0] = something
 * split[1] = NULL;
 * split[2] = NULL;
 */
static char	**env_split(char *str, char del)
{
	size_t	i;
	char	**split;

	i = 0;
	split = ft_calloc(3, sizeof(char *));
	while (str[i] != del && str[i])
		i++;
	split[0] = ft_substr(str, 0, i);
	if (str[i])
		split[1] = ft_substr(str, i + 1, ft_strlen(str) - 1); // how is this working with length of str? Huh?
	else 
		split[1] = NULL;
	return (split);
}

void	change_(t_data *data)
{
	t_env	*env;
	t_env	*new;
	char	*path;

	env = find_node(data->envp_head, "_");
	path = find_path(data, "env");
	env->value = path;
	env->keyvalue = ft_strjoin("_=", path);
	if (!find_node(data->envp_head, "OLDPWD"))
	{
		new = ft_calloc(sizeof(t_env), 1);
		new->keyvalue = ft_strdup("OLDPWD");
		new->key = ft_strdup("OLDPWD");
		lst_addback(data, new);
	}
}

void	env_innit(t_data *data, char **envp)
{
	char	**tmp;
	t_env	*lst;

	data->envp_head = malloc(sizeof(t_env));
	if (!data->envp_head)
		return (display_error(data, "Malloc failed", true));
	lst = data->envp_head;
	while (*envp != NULL)
	{
		lst->keyvalue = *envp;
		tmp = env_split(*envp, '=');
		lst->key = tmp[0];
		lst->value = tmp[1];
		envp++;
		if (*envp != NULL)
		{
			lst->next = malloc(sizeof(t_env));
			if (!lst->next)
				return (display_error(data, "Malloc failed", true));
			lst = lst->next;
		}
	}
	lst->next = NULL;
	change_(data);
}
