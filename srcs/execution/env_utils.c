/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 23:06:48 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/20 23:47:32 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


size_t	get_lstsize(t_env *lst)
{
	size_t	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

t_env	*find_node(t_env *lst, char *key)
{
	ft_printf_fd(STDERR_FILENO, "in find_node\n");
	while (lst != NULL)
	{
		if (ft_strncmp(lst->key, key, ft_strlen(lst->key)) == 0 && \
			!ft_strncmp(key, lst->key, ft_strlen(key)))
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
	// if (!lst)
	// 	return (display_error(data, "Env list failed to create", true), NULL);
	env = malloc((get_lstsize(data->envp_head) + 1) * sizeof(char *)); // count size each time
	while (lst != NULL)
	{
		// if (lst && lst->keyvalue)
		env[i] = ft_strdup(lst->keyvalue);
		lst = lst->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}
