/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 23:06:48 by mialbert          #+#    #+#             */
/*   Updated: 2022/10/26 18:16:28 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	lstclear(t_env *lst)
{
	t_env	*tmp;

	if (!lst)
		return ;
	tmp = (t_env *)lst;
	while (tmp != NULL)
	{
		tmp = (tmp)->next;
		free(lst->keyvalue);
		free(lst->key);
		free(lst->value);
		free(lst);
		lst = tmp;
	}
	tmp = NULL;
}

void	free_data(t_data *data)
{
	size_t	i;

	i = 0;
	free_2d_guard(&data->paths);
	lstclear((void *)data->envp_head);
	free(data->pwd);
	while (i < data->groupc)
	{
		free_2d_guard(&data->group[i].full_cmd);
		// lstclear((void *)data->group[i].outfile);
		// lstclear((void *)data->group[i].infile);
		i++;
	}
}

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
	if (!lst)
		return (display_error(data, "Env list failed to create", true), NULL);
	env = malloc((data->envpc + 1) * sizeof(char *));
	while (lst->next != NULL)
	{
		env[i++] = ft_strdup(lst->keyvalue);
		lst = lst->next;
	}
	env[i] = NULL;
	return (env);
}
