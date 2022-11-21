/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 22:46:32 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/20 23:50:40 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * With the false param free_env_node only frees 
 * the content of the node and not the entire node,
 * which are then changed to more accurately replicate Bash.
 */
void	change_(t_data *data)
{
	t_env	*env;
	char	*path;

	env = find_node(data->envp_head, "_");
	if (env != NULL)
	{
		free_env_node(env, false);
		path = find_path(data, "env");
		env->key = ft_strdup("_");
		env->value = path;
		env->keyvalue = ft_strjoin("_=", path);
		env->printed = true;
	}
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
char	**env_split(char *str, char del)
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

void	env_innit(t_data *data, char **envp)
{
	char	**tmp;
	t_env	*lst;

	data->envp_head = malloc(sizeof(t_env));
	// if (!data->envp_head)
		// return (display_error(data, "Malloc failed", true));
	lst = data->envp_head;
	while (*envp != NULL)
	{
		lst->keyvalue = ft_strdup(*envp);
		tmp = env_split(*envp, '=');
		lst->key = tmp[0];
		if (ft_strncmp(lst->key, "SHLVL", ft_strlen(lst->key) == 0))
			lst->value = ft_itoa(ft_atoi(tmp[1]) + 1);
		else
			lst->value = tmp[1];
		free(tmp);
		envp++;
		// printf("%s\n", *envp);
		if (*envp != NULL)
		{
			lst->next = malloc(sizeof(t_env));
			// if (!lst->next)
			// 	return (display_error(data, "Malloc failed", true));
			lst = lst->next;
		}
	}
	lst->next = NULL;
	change_(data);
}
