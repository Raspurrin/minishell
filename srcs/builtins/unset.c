/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 20:10:21 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/22 23:30:15 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	move_pointers(t_env *envp_head, char *var)
{
	t_env	*prev;
	t_env	*lst;

	prev = envp_head;
	lst = envp_head;
	while (lst != NULL)
	{
		if (ft_strcmp(var, lst->key) == 0)
		{
			if (lst == envp_head && lst->next)
				envp_head = lst->next;
			else if (lst->next)
				prev->next = lst->next;
			free_env_node(lst, 1);
			if (lst->next == NULL)
				prev->next = NULL;
			break ;
		}
		prev = lst;
		lst = lst->next;
	}
}

/**
 * Unsetting env node. Whenever the right node has been found, 
 * set the next pointer of the previous node to the following node: 
 * [prev]->[cur]->[next]	->		[prev]->[next]
 * Or if node is the head, just make the next node the start of the list.
 */
uint32_t	unset(t_data *data, t_group *group)
{
	size_t		i;
	uint32_t	exit;

	i = 1;
	exit = 0;
	if (!group->full_cmd[i])
		return (1);
	while (group->full_cmd[i])
	{
		if (!check_key(group, group->full_cmd[i], group->full_cmd[i + 1]))
			return (exit);
		if (ft_strcmp(group->full_cmd[i], "PWD") == 0)
			init_oldpwd(data);
		move_pointers(data->envp_head, group->full_cmd[i]);
		i++;
	}
	return (exit);
}
