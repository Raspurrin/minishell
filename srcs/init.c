/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 22:46:32 by mialbert          #+#    #+#             */
/*   Updated: 2022/10/30 11:46:14 by mialbert         ###   ########.fr       */
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

static char **env_split(char *str, char del)
{
	size_t	i;
	char **split;

	split = malloc(3 * sizeof(char *));
	while (str[i] != del)
		i++;
	split[0] = ft_substr(str, 0, i - 1);
	split[1] = ft_substr(str, i, ft_strlen(str));
	return (split);
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
}
