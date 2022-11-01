/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 01:52:49 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/01 19:49:27 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * First I check for valid input. "env env env" should work, 
 * any other input should throw an error. 
 * Printing out the environmental variables that have a value, 
 * otherwise they are ignored. 
 */
void	print_env(t_data *data, t_group *group)
{
	t_env	*lst;
	size_t	i;

	i = 0;
	while (group->full_cmd[i] && ft_strncmp(group->full_cmd[i], \
							"env", ft_strlen(group->full_cmd[i])))
		i++;
	if (group->full_cmd[i] != NULL)
		return (ft_printf_fd(STDERR_FILENO, "env: %s: No such file or directory", \
																group->full_cmd[i]);
	lst = data->envp_head;
	while (lst != NULL)
	{
		if (lst->value)
			printf("%s\n", lst->keyvalue);
		lst = lst->next;
	}
}
