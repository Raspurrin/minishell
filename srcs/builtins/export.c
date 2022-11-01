/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 20:10:18 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/01 19:15:43 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	set_printed_false(t_data *data)
{
	t_env	*lst;

	lst = data->envp_head;
	while (lst->next != NULL)
	{
		lst->printed = false;
		lst = lst->next;
	}
}

void	export(t_data *data, t_group *group)
{
	t_env	*lst;
	t_env	*smol;
	t_env	*tmp;

	(void)group;
	lst = data->envp_head;
	smol = lst;
	while (lst != NULL)
	{
		tmp = data->envp_head;
		while (tmp->printed == true)
			tmp = tmp->next;
		smol = tmp;
		while (tmp->next != NULL)
		{
			if ((ft_strncmp(tmp->key, smol->key, ft_strlen(tmp->key)) < 0) \
													&& tmp->printed == false)
				smol = tmp;
			tmp = tmp->next;
		}
		smol->printed = true;
		printf("declare -x %s=\"%s\"\n", smol->key, smol->value);
		lst = lst->next;
	}
	set_printed_false(data);
}

// char **env_split(size_t	wcount, )

void	export_add(t_data *data, t_group *group)
{
	size_t	i;
	t_env	*lst;
	t_env	*dup;
	t_env	*new;
	char	**tmp;

	i = 1;
	while (group->full_cmd[i])
	{
		tmp = ft_split(group->full_cmd[1], '=');
		dup = find_node(data->envp_head, tmp[0]);
		// t_env *env = find_node(data->envp_head, tmp[0]);
		if (dup)
		{
			dup->value = tmp[1];
			dup->keyvalue = group->full_cmd[1];
			return ;
		}
		new = ft_calloc(sizeof(t_env), 1);
		new->keyvalue = group->full_cmd[i];
		new->key = tmp[0];
		new->value = tmp[1];
		new->printed = false;
		new->next = NULL;
		lst = data->envp_head;
		while (lst->next != NULL)
			lst = lst->next;
		lst->next = new;
		i++;
	}
}
