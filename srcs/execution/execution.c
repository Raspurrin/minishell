/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:48:19 by mialbert          #+#    #+#             */
/*   Updated: 2022/10/14 04:08:49 by mialbert         ###   ########.fr       */
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
	printf("hi\n");
	printf("group_i: %zu\n", group_i);
	cmd = ft_strjoin("/", data->group[group_i].full_cmd[0]);
	while (data->paths[i++])
	{
		path = ft_strjoin(data->paths[i - 1], cmd);
		if (access(path, F_OK | X_OK) == 0)
		{
			printf("path: %s\n", path);
			return (free(cmd), path);
		}
		else
			free(path);
	}
	free(cmd);
	return (display_error(data, "path failed", true), NULL);
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
	outfiles(&data->group[i]);
	close(fd[0]);
	close(fd[1]);
	ft_printf_fd(STDERR_FILENO, "data->group[i].full_cmd: %s\n", *(data->group[i].full_cmd));
	printf("%s", path);
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
	size_t	i;
	int32_t	pid;
	int32_t	fd[2];

	i = 0;
	while (i < (size_t)data->groupc)
	{
		// if (data->group->infile)
		infiles(data, &data->group[i]);
		pipe(fd);
		pid = fork();
		if (pid == -1)
			display_error(data, "fork failed", true);
		if (pid == 0)
			child_cmd(data, i, fd, env);
		waitpid(pid, NULL, 0);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		i++;
	}
}

void	execution(t_data *data, char **env)
{
	exec_cmds(data, env);
	free_at_exit(data);
}
