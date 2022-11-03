/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 03:22:30 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/02 18:19:33 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_oldpwd(t_data *data)
{
	t_env	*lst;

	lst = find_node(data->envp_head, "OLDPWD");
	lst->value = data->pwd;
}

static bool	check_error(t_group *group)
{
	if (!access(group->full_cmd[1], R_OK | F_OK))
	{
		ft_printf_fd(STDOUT_FILENO, "cd: no such file or direcotry: \
											%s", group->full_cmd[1]);
		return (false);
	}
	return (true);
}

/**
 * It seems like the environmental variable PWD doesn't change its value 
 * after using chdir(), which is why I am manually changing this string.
*/
void	cd(t_data *data, t_group *group)
{
	size_t	len;
	t_env	*env;

	if (!check_error(group))
		return ;
	env = find_node(data->envp_head, "PWD");
	chdir(group->full_cmd[1]);
	if (data->pwd)
		update_oldpwd(data);
	if (ft_strncmp(group->full_cmd[1], "../", 3) == 0) // what if ../owfaijfoewaifj
	{
		if (group->full_cmd[2] == NULL)
		{
			len = ft_strlen(data->pwd);
			while (data->pwd[len] != '/')
				len--;
			printf("len: %zu\n", len);
			if (len == 0)
				data->pwd = "/";
			else
				data->pwd = ft_substr(data->pwd, 0, len);
			env->value = data->pwd;
		}
	}
	else
	{
		data->pwd = ft_strjoin(data->pwd, "/");
		data->pwd = ft_strjoin(data->pwd, group->full_cmd[1]);
	}
}
