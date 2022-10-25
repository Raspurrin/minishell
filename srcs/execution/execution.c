/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:48:19 by mialbert          #+#    #+#             */
/*   Updated: 2022/10/25 17:02:35 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Full_cmd contains the cmd with all its flags in seperate elements: "ls -la"
 * It is included in my data struct because it is later used in execve!
 * Cmd takes the first element and joins it with '/': "/ls"
 * Path combines the path with cmd: "usr/bin/ls" and checks its accessibility.
 */
static char	*find_path(t_data *data, size_t	group_i)
{
	size_t	i;
	char	*cmd;
	char	*path;

	i = 0;
	cmd = ft_strjoin("/", data->group[group_i].full_cmd[0]);
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

bool	builtin_check(t_data *data, t_group *group)
{
	if (ft_strncmp(group->full_cmd[0], "cd", 2) == 0)
		unset(data, group);
	else if (ft_strncmp(group->full_cmd[0], "echo", 4) == 0)
		echo(data, group);
	else if (ft_strncmp(group->full_cmd[0], "env", 3) == 0)
		print_env(data, group);
	else if (ft_strncmp(group->full_cmd[0], "exit", 4) == 0)
		exit_check(data, group);
	else if (ft_strncmp(group->full_cmd[0], "export", 6) == 0)
		export(data, group);
	else if (ft_strncmp(group->full_cmd[0], "pwd", 3) == 0)
		pwd(data, group);
	else if (ft_strncmp(group->full_cmd[0], "unset", 5) == 0)
		unset(data, group);
	else
		return (false);
	return (true);
}

/**
 * First I find the correct path for the next command in find_path()
 * Execve will execute another program which takes over the entire process.
 * Which is why this is done in a child process. 
 * At the very last itteration, the output is redirected to a file. 
 */
static void	child_cmd(t_data *data, size_t i, int32_t fd[2], char **env)
{
	char	*path;

	path = find_path(data, i);
	if (!infiles(data, &data->group[i]) && i > 0)
		dup2(data->tmp_fd, STDIN_FILENO);
	if (!outfiles(data, &data->group[i]) && i != data->groupc - 1)
		dup2(fd[WRITE], STDOUT_FILENO);
	close(fd[WRITE]);
	if (i > 0)
		close(data->tmp_fd);
	if (builtin_check(data, data->group) == true)
		return (free(path));

	if (execve(path, data->group[i].full_cmd, env) == -1)
	{
		free(path);
		display_error(data, "execve failed", true);
	}
}

/**
 * Creating new child processes for each command executed, facilitating
 * inter-process communication with pipes and redirecting output and input
 * from the commands to STDIN and STDOUT with dup2, which will then be used
 * by the next command. Closing the fds so the program doesn't wait for input.
 */
static void	exec_cmds(t_data *data, char **env)
{
	size_t		i;
	int32_t		pid;
	int32_t		fd[2];

	i = 0;
	if (data->groupc == 1)
	{
		infiles(data, data->group);
		outfiles(data, data->group);
		builtin_check(data, data->group);
	}
	while (i < (size_t)data->groupc)
	{
		pipe(fd);
		pid = fork();
		if (pid == -1)
			display_error(data, "fork failed", true);
		else if (pid == 0)
			child_cmd(data, i, fd, env);
		waitpid(pid, NULL, 0);
		if (i > 0)
			close(data->tmp_fd);
		data->tmp_fd = fd[READ];
		close(fd[WRITE]);
		i++;
	}
}

void	execution(t_data *data, char **env)
{
	exec_cmds(data, env);
	free_at_exit(data);
}
