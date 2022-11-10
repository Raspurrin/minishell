/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:48:19 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/10 02:47:31 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*relative_path(char *path)
{
	size_t	sub;
	size_t	len;
	
	sub = 0;
	if (ft_strncmp(path, "./", 2) == 0)
		return (ft_substr(path, 2, ft_strlen(path) - 2));
	while (ft_strncmp(path, "../", 3) == 0)
	{
		path += 3;
		sub++;
	}
	len = ft_strlen(path);
	while (sub > 0)
	{
		while (path[len] != '/')
			len--;
		sub--;
	}
	return (ft_substr(path, 0, len));
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

	i = 0;
	path_innit(data);
	if (!data->paths)
		return (NULL);
	if (ft_strchr(cmd_name, '/'))
	{
		path = relative_path(cmd_name);
		if (access(path, F_OK | X_OK) == 0)
			return (cmd_name);
		return (display_error(data, "path failed", true), NULL);
	}
	cmd = ft_strjoin("/", cmd_name);
	while (data->paths[i++])
	{
		path = ft_strjoin(data->paths[i - 1], cmd);
		if (access(path, F_OK | X_OK) == 0)
			return (free(cmd), path);
		else
			free(path);
	}
	free(cmd);
	return (display_error(data, "path failed", true), NULL);
}

// but what if full_cmd[0] == "echowfjselfijal";
bool	builtin_check(t_data *data, t_group *group)
{
	(void)data;
	if (ft_strncmp(group->full_cmd[0], "echo", 4) == 0)
		group->builtin = &echo;
	else if (ft_strncmp(group->full_cmd[0], "env", 3) == 0)
		group->builtin = &env;
	else if (ft_strncmp(group->full_cmd[0], "exit", 4) == 0)
		group->builtin = &exit_check;
	else if (ft_strncmp(group->full_cmd[0], "export", 6) == 0) 
	{
		if (group->full_cmd[1] == NULL)
			group->builtin = &export;
		else
			group->builtin = &export_add;
	}
	else if (ft_strncmp(group->full_cmd[0], "pwd", 3) == 0)
		group->builtin = &pwd;
	else if (ft_strncmp(group->full_cmd[0], "unset", 5) == 0)
		group->builtin = &unset;
	else
		return (fprintf(stderr, "no builtin found: %p\n", group->builtin), false);
	return (true);
}

static void	close_fds(t_data *data, size_t i, int32_t fd[2])
{
	close(fd[WRITE]);
	if (i > 0)
		close(data->tmp_fd);
	if (i == data->groupc - 1)
		close(fd[READ]);
}

/**
 * First I find the correct path for the next command in find_path()
 * Execve will execute another program which takes over the entire process.
 * Which is why this is done in a child process. 
 * At the very last itteration, the output is redirected to a file. 
 */
static void	child_cmd(t_data *data, size_t i, int32_t fd[2])
{
	char	*path;
	char	**env;

	if (!infiles(data, &data->group[i]) && i > 0)
		dup2(data->tmp_fd, STDIN_FILENO);
	if (!outfiles(data, &data->group[i]) && i != data->groupc - 1)
		dup2(fd[WRITE], STDOUT_FILENO);
	close_fds(data, i, fd);
	if (builtin_check(data, data->group) == true)
	{
		data->group[i].builtin(data, &data->group[i]);
		return ;
	}
	env = env_2darr(data, data->envp_head);
	path = find_path(data, data->group[i].full_cmd[0]);
	if (execve(path, data->group[i].full_cmd, env) == -1)
		return (free(path), free(env), display_error(data, "execve failed", true));
}

/**
 * Creating new child processes for each command executed, facilitating
 * inter-process communication with pipes and redirecting output and input
 * from the commands to STDIN and STDOUT with dup2, which will then be used
 * by the next command. Closing the fds so the program doesn't wait for input.
 */
static void	exec_cmds(t_data *data)
{
	size_t	i;
	int32_t	pid;
	int32_t	fd[2];

	i = 0;
	if (data->groupc == 1 && builtin_check(data, data->group))
	{
		infiles(data, data->group);
		outfiles(data, data->group);
		data->group[i].builtin(data, &data->group[i]);
		return ;
	}
	while (i < (size_t)data->groupc)
	{
		pipe(fd);
		pid = fork();
		if (pid == -1)
			display_error(data, "fork failed", true);
		if (pid == 0)
			child_cmd(data, i, fd);
		if (i > 0)
			close(data->tmp_fd);
		data->tmp_fd = fd[READ];
		close(fd[WRITE]);
		i++;
	}
	close(fd[READ]);
}

void	execution(t_data *data)
{
	size_t	i;
	int32_t	status;

	i = 0;
	exec_cmds(data);
	while (i < data->groupc)
	{
		wait(&status);
		data->status = status;
		i++;
	}
	free_at_exit(data);
}
