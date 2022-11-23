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

/**
 * Unsetting env node. Whenever the right node has been found, 
 * set the next pointer of the previous node to the following node: 
 * [prev]->[cur]->[next]	->		[prev]->[next]
 * Or if node is the head, just make the next node the start of the list.
 */
int8_t	unset(t_data *data, t_group *group)
{
	size_t	i;
	t_env	*lst;
	t_env	*prev;
	int8_t	exit;

	i = 1;
	exit = 0;
	if (!group->full_cmd[i])
		return (1);
	while (group->full_cmd[i])
	{
		if (!check_key(group->full_cmd[i]))
		{
			exit = 1;
			display_error(IDENT, join_err(group->full_cmd[i], NULL), \
														NULL, group);
			if (!group->full_cmd[i + 1])
				return (exit);
			i++;
		}
		lst = data->envp_head;
		prev = lst;
		while (lst != NULL)
		{
			if (ft_strcmp(group->full_cmd[i], lst->key) == 0)
			{
				if (lst == data->envp_head && lst->next)
					data->envp_head = lst->next;
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
		i++;
	}
	return (exit);
}
