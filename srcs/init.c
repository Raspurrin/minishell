/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 22:46:32 by mialbert          #+#    #+#             */
/*   Updated: 2022/10/28 20:46:40 by mialbert         ###   ########.fr       */
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
		tmp = ft_split(*envp, '=');
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
