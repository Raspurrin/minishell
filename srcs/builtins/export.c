/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 20:10:18 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/20 03:23:47 by mialbert         ###   ########.fr       */
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

bool	export(t_data *data, t_group *group)
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
	return (set_printed_false(data), true);
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

static bool check_export(char *export)
{
	ft_printf_fd(STDERR_FILENO, "check_export: %s\n", export);
	while (*export)
	{
		if ((!(ft_isalpha(*export)) && *export != '_' && *export != '='))
		{
			ft_printf_fd(STDERR_FILENO, "Cause export fails: %c", *export);
			return (false);
		}
		export++;
	}
	return (true);
}

/**
 * example:
 * export something=====blue something= USER=mialbert
 */
bool	export_add(t_data *data, t_group *group)
{
	size_t	i;
	t_env	*dup;
	t_env	*new;
	char	**tmp;

	i = 1;
	ft_printf_fd(STDERR_FILENO, "export add\n");
	print_2d_fd(group->full_cmd, STDERR_FILENO);
	while (group->full_cmd[i])
	{
		ft_printf_fd(STDERR_FILENO, "group->full_cmd[i]: %s\n", group->full_cmd[i]);
		while (!check_export(group->full_cmd[i])) // this is retarded, pls be more smart
		{
			ft_printf_fd(STDERR_FILENO, "check_export failed\n");
			if (!group->full_cmd[i + 1])
				return (false);
			i++;
		}
		tmp = env_split(group->full_cmd[i], '=');
		ft_printf_fd(STDERR_FILENO, "tmp[0]: %s\n", tmp[0]);
		dup = find_node(data->envp_head, tmp[0]);
		// t_env *env = find_node(data->envp_head, tmp[0]);
		if (dup)
		{
			free(dup->keyvalue);
			if (tmp[1])
			{
				free(dup->value);
				dup->value = tmp[1];
			}
			dup->keyvalue = ft_strdup(group->full_cmd[i]);
			// free(group->full_cmd[i]);
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
		i++;
	}
	return (true);
}
