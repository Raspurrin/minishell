/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 22:46:32 by mialbert          #+#    #+#             */
/*   Updated: 2022/10/07 23:45:23 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_path(t_data *data, char **envp)
{
	char	*tmp;

	while (*envp != NULL)
	{
		if (ft_strncmp("PATH", *envp, 4) == 0)
		{
			data->paths = ft_split(*envp, ':');
			tmp = ft_substr(data->paths[0], 5, \
							ft_strlen(data->paths[0]) - 5);
			free (data->paths[0]);
			data->paths[0] = tmp;
		}
		envp++;
		data->envpc++;
	}
	return ;
}

void	init_env(t_data *data, char **envp)
{
	char	**tmp;
	t_env	*lst;

	data->envp_head = malloc(sizeof(t_env));
	lst = data->envp_head;
	while (*envp != NULL)
	{
		lst->keyvalue = *envp;
		tmp = ft_split(*envp, '=');
		lst->key = tmp[0];
		lst->value = tmp[1];
		envp++;
		if (envp != NULL)
			lst->next = malloc(sizeof(t_env));
		lst = lst->next;
	}
	lst->next = NULL;
}



void	init(t_data *data, char **envp)
{
	init_path(data, envp);
	init_env(data, envp);
}
