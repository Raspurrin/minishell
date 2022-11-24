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

uint32_t	export(t_data *data, t_group *group)
{
	t_env	*lst;
	t_env	*smol;
	t_env	*tmp;

	(void)group;
	lst = data->envp_head;
	smol = lst;
	if (!lst)
		return (false);
	while (lst->next != NULL)
	{
		tmp = data->envp_head;
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

// char **env_split(size_t	wcount, )

void	lst_addback(t_data *data, t_env *new)
{
	t_env	*lst;

	lst = data->envp_head;
	while (lst->next != NULL)
		lst = lst->next;
	lst->next = new;
}

bool	check_key(char *key)
{
	if (*key == '=')
		return (false);
	while (*key)
	{
		if ((!(ft_isalpha(*key)) && (!ft_isalnum(*key)) \
					&& *key != ' ' && *key != '_' && *key != '='))
			return (false);
		key++;
	}
	return (true);
}

/**
 * example:
 * export something=====blue something= USER=mialbert
 */
uint32_t	export_add(t_data *data, t_group *group)
{
	size_t	i;
	t_env	*dup;
	t_env	*new;
	char	**tmp;
	uint32_t	exit;

	i = 1;
	exit = 0;
	print_2d_fd(group->full_cmd, STDERR_FILENO);
	while (group->full_cmd[i])
	{
		if (!check_key(group->full_cmd[i]))
		{
			exit = 1;
			display_error(NODIR, join_err(group->full_cmd[i], NULL), NULL, group);
			if (!group->full_cmd[i + 1])
				return (exit);
		}
		else
		{
			tmp = env_split(group->full_cmd[i], '=');
			dup = find_node(data->envp_head, tmp[0]);
			if (dup)
			{
				free(dup->keyvalue);
				if (tmp[1])
				{
					free(dup->value);
					dup->value = tmp[1];
				}
				dup->keyvalue = ft_strdup(group->full_cmd[i]);
				free(tmp[0]);
				free(tmp);
			}
			else
			{
				new = ft_calloc(sizeof(t_env), 1);
				new->keyvalue = ft_strdup(group->full_cmd[i]);
				new->key = tmp[0];
				new->value = tmp[1];
				free(tmp);
				new->printed = false;
				new->next = NULL;
				lst_addback(data, new);
			}
		}
		i++;
	}
	return (exit);
}
