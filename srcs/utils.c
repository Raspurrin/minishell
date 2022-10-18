/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 23:06:48 by mialbert          #+#    #+#             */
/*   Updated: 2022/10/18 18:27:25 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	lstclear(void **lst)
{
	t_env	*tmp;

	tmp = (t_env *)lst;
	if (!lst)
		return ;
	while (tmp != NULL)
	{
		tmp = (tmp)->next;
		free(*lst);
		*lst = tmp;
	}
	tmp = NULL;
}

void	free_data(t_data *data)
{
	size_t	i;

	i = 0;
	free_2d_guard(&data->paths);
	lstclear((void **)data->envp_head);
	free(data->pwd);
	while (i < data->groupc)
	{
		free_2d_guard(&data->group[i].full_cmd);
		lstclear((void *)data->group[i].outfile);
		lstclear((void *)data->group[i].infile);
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
	env = malloc(data->envpc * sizeof(char *));
	while (lst->next != NULL)
	{
		env[i++] = lst->keyvalue;
		lst = lst->next;
	}
	return (env);
}
