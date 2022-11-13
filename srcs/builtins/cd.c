/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 03:22:30 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/13 05:44:28 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * if PWD is unset OLDPWD's value changes to ""
 * Otherwise OLDPWD gets PWD's old value before I change PWD's value in cd.
 */
static void	update_oldpwd(t_data *data)
{
	t_env	*oldpwd;
	t_env	*pwd;

	oldpwd = find_node(data->envp_head, "OLDPWD");
	pwd = find_node(data->envp_head, "PWD");
	if (!pwd)
		oldpwd->value = "";
	else 
		oldpwd->value = data->pwd;
}

/**
 * @param relative The relative path to edit path with. Ex: ../../evals/ft_irc
 * outcome: Documents/evals/ft_irc
 * @param path The path you want to start with. 
 * Ex: Documents/my_projects/minishell
 */
char	*relative_path(char *relative, char *path)
{
	size_t	len;
	char	*folder;
	
	len = 0;
	if (ft_strncmp(relative, "./", 2) == 0)
		relative += 2;
	while (ft_strncmp(relative, "../", 3) == 0)
	{
		len = pos_char_end(path, '/');
		path = ft_substr(path, 0, len);
		relative += 3;
	}
	while (relative)
	{
		len = pos_char_start(relative, '/');
		folder = ft_substr(relative, 0, len);
		path = ft_strjoin(path, folder);
		relative += len;
	}
	if (access(path, F_OK | X_OK) == 0)
		return (path);
	return (NULL);
}

char	*absolute_or_relative(char *path, char *old_path)
{
	if (access(path, F_OK | X_OK) == 0)
		return (path);
	path = relative_path(path, old_path);
	if (!path)
		return (NULL);
	return (path);
}

/**
 * Chdir returns -1 if the path cannot be changed. It can accept relative paths. 
 * Oldpwd will be changed first, then I check if the path already works,
 * in case of an absolute path given, otherwise the relative path will be solved.
 * If PWD is not unset, the value will be changed as well.
 * data->pwd exists in case PWD doesn't, since pwd should still work.
*/
void	cd(t_data *data, t_group *group)
{
	t_env	*env;

	if (chdir(group->full_cmd[1]) == -1)
		return (perror(NULL));
	update_oldpwd(data);
	data->pwd = absolute_or_relative(group->full_cmd[1], data->pwd);
	env = find_node(data->envp_head, "PWD");
	if (env)
		env->value = data->pwd;
}
