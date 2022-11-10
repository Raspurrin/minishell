/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 23:06:48 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/10 01:50:09 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Not freeing keyvalue because it is directly taken from
 * envp from main. 
 */
void	free_env_node(t_env *lst, bool free_all)
{
	if (lst->keyvalue)
		free(lst->keyvalue);
	if (lst->key)
		free(lst->key);
	if (lst->value)
		free(lst->value);
	ft_bzero(lst, sizeof(lst));
	if (lst && free_all == true)
		free(lst);
}

void	free_env_lst(t_env *lst)
{
	t_env	*tmp;

	if (!lst)
		return ;
	tmp = lst;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		free_env_node(lst, true);
		lst = tmp;
	}
	tmp = NULL;
}

void	lst_clear(void *file_lst)
{
	t_infile	*lst;
	t_infile	*tmp;

	if(!file_lst)
		return ;
	tmp = (t_infile *)file_lst;
	lst = tmp;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		if (lst->name)
			free(lst->name);
		if (lst)
			free(lst);
		lst = tmp;
	}
	tmp = NULL;
}

void	free_data(t_data *data)
{
	size_t	i;

	i = 0;
	free_2d(data->paths);
	free_env_lst((void *)data->envp_head);
	if (data->pwd)
	{
		fprintf(stderr, "%s DESERVES FREEDOM AND I WILL FREE IT\n", data->pwd);
		free(data->pwd);
		data->pwd = NULL;
	}
	while (i < data->groupc)
	{
		free_2d_guard(&data->group[i].full_cmd);
		if (data->group[i].outfile)
			lst_clear((void *)data->group[i].outfile);
		if (data->group[i].infile)
			lst_clear((void *)data->group[i].infile);
		if (data->group[i].builtin)
			free(data->group[i].builtin);
		if (&data->group[i])
			free(&data->group[i]);
		i++;
	}
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
		if (ft_strncmp(lst->key, key, ft_strlen(lst->key)) == 0)
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
	env = malloc((get_lstsize(data->envp_head) + 1) * sizeof(char *)); // count size each time
	while (lst->next != NULL)
	{
		env[i] = ft_strdup(lst->keyvalue);
		lst = lst->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}
