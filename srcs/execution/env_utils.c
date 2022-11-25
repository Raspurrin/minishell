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

t_env	*env_addvalue(t_env *lst, char **tmp, char *keyvalue)
{
	lst->keyvalue = ft_strdup(keyvalue);
	lst->key = tmp[0];
	lst->value = tmp[1];
	lst->printed = false;
	lst->next = NULL;
	free(tmp);
	return (lst);
}

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
	if (!lst)
		return (ft_printf_fd(STDERR_FILENO, "Env list failed to create: %s %s" \
												, __LINE__, __FILE__), NULL);
	env = malloc((get_lstsize(data->envp_head) + 1) * sizeof(char *));
	while (lst != NULL)
	{
		env[i] = ft_strdup(lst->keyvalue);
		lst = lst->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}

void	lst_addback(t_data *data, t_env *new)
{
	t_env	*lst;

	lst = data->envp_head;
	while (lst->next != NULL)
		lst = lst->next;
	lst->next = new;
}
