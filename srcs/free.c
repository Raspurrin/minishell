/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 06:36:38 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/22 20:00:18 by pmoghadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Not freeing keyvalue because it is directly taken from
 * envp from main. 
 */
void	free_env_node(t_env *lst, bool free_all)
{
	if (!lst)
		return ;
	if (lst->keyvalue)
		free(lst->keyvalue);
	if (lst->key)
		free(lst->key);
	if (lst->value)
		free(lst->value);
	ft_bzero(lst, sizeof(lst));
	if (lst && free_all == true)
		free(lst);
	lst = NULL;
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
		{
			free(lst->name);
			lst->name = NULL;
		}
		if (lst)
		{
			free(lst);
			lst = NULL;
		}
		lst = tmp;
	}
	tmp = NULL;
}

void	free_groups(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->groupc && data->group && &data->group[i])
	{
		if (data->group[i].full_cmd)
			free_2d(data->group[i].full_cmd);
		if (data->group[i].outfile)
			lst_clear((void *)data->group[i].outfile);
		if (data->group[i].infile)
			lst_clear((void *)data->group[i].infile);
		i++;
	}
	free(data->group);
	data->group = NULL;
}

void	free_data(t_data *data)
{
	free_env_lst((void *)data->envp_head);
	free_groups(data);
}
