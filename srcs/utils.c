/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 23:06:48 by mialbert          #+#    #+#             */
/*   Updated: 2022/10/17 11:07:19 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*find_node(t_env *lst, char *key)
{
	while (lst != NULL)
	{
		if (ft_strncmp(lst->key, key, ft_strlen(key)) == 0)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

char	**env_2darr(t_data *data, t_env *lst)
{
	char	**env;
	size_t	i;

	i = 0;
	env = malloc(data->envpc * sizeof(char *));
	while (lst->next != NULL)
	{
		env[i++] = lst->keyvalue;
		lst = lst->next;
	}
	return (env);
}
