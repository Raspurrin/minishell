/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:48:19 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/08 01:50:50 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Full_cmd contains the cmd with all its flags in seperate elements: "ls -la"
 * It is included in my data struct because it is later used in execve!
 * Cmd takes the first element and joins it with '/': "/ls"
 * Path combines the path with cmd: "usr/bin/ls" and checks its accessibility.
 */
char	*find_path(t_data *data, char *cmd_name)
{
	size_t	i;
	char	*cmd;
	char	*path;

	i = 0;
	// printf("hi\n");
	// printf("group_i: %zu\n", group_i);
	// ft_printf_fd(STDERR_FILENO, "data->group[group_i].full_cmd[0]: %s\n", data->group[group_i].full_cmd[0]);
	path_innit(data);
	if (!data->paths)
		return (NULL);
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
	fprintf(stderr, "inside builtin_check\n");
	if (ft_strncmp(group->full_cmd[0], "echo", 4) == 0)
		group->builtin = &echo;
	else if (ft_strncmp(group->full_cmd[0], "env", 3) == 0)
		group->builtin = &env;
	else if (ft_strncmp(group->full_cmd[0], "exit", 4) == 0)
		group->builtin = &exit_check;
	else if (ft_strncmp(group->full_cmd[0], "export", 6) == 0) // check in func which export 
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
	// fprintf(stderr, "oh no this didnt work why didnt this work this should have worked\n");
	return (true);
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

	ft_printf_fd(STDERR_FILENO, "------------\nin child process:\n");
	if (!infiles(data, &data->group[i]) && i > 0)
	{
		ft_printf_fd(STDERR_FILENO, "dupping tmp_fd(previous fd[0]) to STDIN\n");
		dup2(data->tmp_fd, STDIN_FILENO);
	}
	ft_printf_fd(STDERR_FILENO, "child_cmd - i: %d\n", i);
	if (!outfiles(data, &data->group[i]) && i != data->groupc - 1)
	{
		ft_printf_fd(STDERR_FILENO, "Dupping fd[1] to STDOUT\n");
		dup2(fd[WRITE], STDOUT_FILENO);
	}
	close(fd[WRITE]);
	if (i > 0)
		close(data->tmp_fd);
	path = find_path(data, data->group[i].full_cmd[0]);
	print_2d_fd(data->group[i].full_cmd, STDERR_FILENO);
	if (builtin_check(data, data->group) == true)
	{
		ft_printf_fd(STDERR_FILENO, "doing a builtin_check\n");
		unsigned char *func = (unsigned char *)&data->group[i].builtin;
		ft_printf_fd(STDERR_FILENO, "builtin: %p data->group: %p\n", func, &data->group[i]);
		data->group[i].builtin(data, &data->group[i]);
		return ;
	}
	ft_printf_fd(STDERR_FILENO, "before execv\n");
	if (execve(path, data->group[i].full_cmd, env_2darr(data, \
										data->envp_head)) == -1)
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
static void	exec_cmds(t_data *data)
{
	size_t	i;
	int32_t	pid;
	int32_t	fd[2];

	i = 0;
	if (data->groupc == 1 && builtin_check(data, data->group))
	{
		// print_env(data->envp_head);
		infiles(data, data->group);
		outfiles(data, data->group);
		ft_printf_fd(STDERR_FILENO, "before executing function\n");
		data->group[i].builtin(data, &data->group[i]);
		return ;
	}
	while (i < (size_t)data->groupc)
	{
		ft_printf_fd(STDERR_FILENO, "------------\nBegin in parent:\n");
		ft_printf_fd(STDERR_FILENO, "creating pipe\n");
		pipe(fd);
		pid = fork();
		if (pid == -1)
			display_error(data, "fork failed", true);
		if (pid == 0)
			child_cmd(data, i, fd);
		ft_printf_fd(STDERR_FILENO, "------------\nEnd in parent:\n");
		waitpid(pid, NULL, 0);
		if (i > 0)
		{
			ft_printf_fd(STDERR_FILENO, "closing tmp_fd\n");
			close(data->tmp_fd);
		}
		data->tmp_fd = fd[READ];
		close(fd[WRITE]);
		ft_printf_fd(STDERR_FILENO, "closing fd[1]\n");	
		i++;
	}
}

void	execution(t_data *data)
{
	// size_t	i;
	// int32_t	status;

	// i = 0;
	exec_cmds(data);
	// while (i < data->groupc)
	// {
	// 	wait(&status);
	// 	data->status = status;
	// 	i++;
	// }
	free_at_exit(data);
}
