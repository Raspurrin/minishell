/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 20:10:18 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/22 23:30:06 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	set_printed_false(t_data *data)
{
	t_env	*lst;

	lst = data->envp_head;
	while (lst != NULL)
	{
		if (ft_strncmp(lst->key, "_", ft_strlen(lst->key)) != 0)
			lst->printed = false;
		lst = lst->next;
	}
}

t_env	*find_smol(t_env *tmp)
{
	t_env	*smol;

	while (tmp->printed == true && tmp->next != NULL)
		tmp = tmp->next;
	smol = tmp;
	while (tmp != NULL)
	{
		if ((ft_strncmp(tmp->key, smol->key, ft_strlen(smol->key)) < 0 && \
												tmp->printed == false))
			smol = tmp;
		tmp = tmp->next;
	}
	return (smol);
}

uint32_t	export(t_data *data, t_group *group)
{
	t_env	*lst;
	t_env	*smol;

	(void)group;
	lst = data->envp_head;
	if (!lst)
		return (false);
	while (lst->next != NULL)
	{
		smol = find_smol(data->envp_head);
		if (!smol->value)
			ft_printf_fd(STDOUT_FILENO, "declare -x %s\n", smol->key);
		else if (smol->printed == false)
			ft_printf_fd(STDOUT_FILENO, "declare -x %s=\"%s\"\n", smol->key, \
																smol->value);
		smol->printed = true;
		lst = lst->next;
	}
	return (set_printed_false(data), 0);
}
