/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:37:00 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/17 21:17:53 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @param relative The relative path to edit path with. Ex: ../../evals/ft_irc
 * outcome: Documents/evals/ft_irc
 * @param pwd The path you want to start with. 
 * Ex: Documents/my_projects/minishell
 */
char	*relative_path(char *relative, char *pwd)
{
	size_t	len;
	char	*folder;

	len = 0;
	ft_printf_fd(STDERR_FILENO, "in relative_path\n");
	if (ft_strncmp(relative, "./", 2) == 0)
		relative += 2;
	while (ft_strncmp(relative, "../", 3) == 0)
	{
		len = pos_char_end(pwd, '/');
		pwd = ft_substr(pwd, 0, len);
		relative += 3;
	}
	folder = ft_strjoin("/", relative);
	pwd = gnl_strjoin(pwd, folder);
	free(folder);
	if (access(pwd, F_OK | X_OK) == 0)
		return (pwd);
	return (free(pwd), NULL);
}

char	*absolute_or_relative(char *path, char *pwd)
{
	ft_printf_fd(STDERR_FILENO, "in absolute_or_relative\n");
	if (access(path, F_OK | X_OK) == 0)
	{
		ft_printf_fd(STDERR_FILENO, "Yooo ok path\n");
		return (path);
	}
	path = relative_path(path, pwd);
	if (!path || (access(path, F_OK | X_OK) != 0))
	{
		ft_printf_fd(STDERR_FILENO, "bullshit path actually\n");
		return (NULL);
	}
	return (path);
}

/**
 * Full_cmd contains the cmd with all its flags in seperate elements: "ls -la"
 * It is included in my data struct because it is later used in execve!
 * Cmd takes the first element and joins it with '/': "/ls"
 * Path combines the path with cmd: "usr/bin/ls" and checks its accessibility.
 * If a '/' can be found in the string, treat cmd_name as a path already. 
 */
char	*find_path(t_data *data, char *cmd_name)
{
	size_t	i;
	char	*cmd;
	char	*path;
	char	**paths;
	t_env	*node;

	i = 0;
	if (ft_strchr(cmd_name, '/'))
		return (absolute_or_relative(cmd_name, data->pwd));
	node = find_node(data->envp_head, "PATH");
	if (!node)
		return (NULL);
	paths = ft_split(node->value, ':');
	if (!paths)
		return (NULL);
	cmd = ft_strjoin("/", cmd_name);
	while (paths[i++])
	{
		path = ft_strjoin(paths[i - 1], cmd);
		if (access(path, F_OK | X_OK) == 0)
			return (free(cmd), free_2d(paths), path);
		else
			free(path);
	}
	return (free(cmd), free_2d(paths), display_error(data, "path failed", true), NULL);
}
