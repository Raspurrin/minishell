/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 22:46:32 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/25 19:28:39 by pmoghadd         ###   ########.fr       */
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
	char	*shlvl;

	env = find_node(data->envp_head, "_");
	if (env != NULL)
	{
		path = find_path(data, "env");
		free(env->key);
		env->key = ft_strdup("_");
		free(env->value);
		env->value = path;
		free(env->keyvalue);
		env->keyvalue = ft_strjoin("_=", path);
		env->printed = true;
	}
	env = find_node(data->envp_head, "SHLVL");
	if (env != NULL)
	{
		shlvl = ft_itoa(ft_atoi(env->value) + 1);
		free(env->value);
		env->value = shlvl;
		free(env->keyvalue);
		env->keyvalue = ft_strjoin("SHLVL=", env->value);
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
		split[1] = ft_substr(str, i + 1, ft_strlen(str) - 1);
	else
		split[1] = NULL;
	return (split);
}

void	env_innit(t_data *data, char **envp)
{
	char	**tmp;
	t_env	*lst;

	data->envp_head = malloc(sizeof(t_env));
	if (!data->envp_head)
		return (error_line("Env list failed to create", __LINE__, __FILE__, 1));
	lst = data->envp_head;
	while (*envp != NULL)
	{
		tmp = env_split(*envp, '=');
		lst = env_addvalue(lst, tmp, *envp);
		envp++;
		if (*envp != NULL)
		{
			lst->next = malloc(sizeof(t_env));
			if (!lst->next)
				return (error_line("Env list failed to create", \
										__LINE__, __FILE__, 1));
			lst = lst->next;
		}
	}
	lst->next = NULL;
	change_(data);
}
