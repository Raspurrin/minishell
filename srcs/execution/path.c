/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:37:00 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/21 00:08:16 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief If an '/' is in cmd_name it is recognised as a path and will 
 * be resolved. Otherwise I get the env variable PATH and split it by colums, 
 * because in the lifetime of the shell, the env variables can change.
 * I then squash paths from the env PATH together with cmd_name 
 * until a valid path is found.
 * @param cmd_name a command name or absolute or relative path to a command. 
 * ex: ls, /bin/ls or ../../bin/ls.
 * @return a valid path or error
 */
char	*find_path(t_data *data, char *cmd_name)
{
	size_t		i;
	char		*cmd;
	char		*path;
	char		**paths;
	const t_env	*node = find_node(data->envp_head, "PATH");

 	i = 0;
	if (!node)
		return (NULL);
	if (ft_strchr(cmd_name, '/'))
		return (cmd_name);
	paths = ft_split(node->value, ':');
	if (!paths)
		return (NULL);
	cmd = ft_strjoin("/", cmd_name);
	while (paths[i++])
	{
		path = ft_strjoin(paths[i - 1], cmd);
		if (access(path, F_OK | X_OK) == 0)
			return (free(cmd), free_2d(paths), path);
		free(path);
	}
	sprintf(debugBuf + ft_strlen(debugBuf), "I am groot\n");
	return (NULL);
	// return (free(cmd), free_2d(paths), \
	// 		display_error(data, "path failed", true), NULL);
}
