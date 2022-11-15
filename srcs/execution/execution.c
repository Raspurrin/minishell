/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:48:19 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/15 19:29:25 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		return (absolute_or_relative(cmd_name, data->pwd));
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
	ft_printf_fd(STDERR_FILENO, "in builtlin_check, cmd: %s\n", group->full_cmd[0]);
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
	ft_printf_fd(STDERR_FILENO, "group->builtin: %p\n", group->builtin);
	return (true);
}

static void	close_fds(t_data *data, size_t i, int32_t fd[2])
{
	ft_printf_fd(STDERR_FILENO, "closing fd[WRITE]\n");
	close(fd[WRITE]);
	if (i > 0)
	{
		ft_printf_fd(STDERR_FILENO, "closing data->tmp_fd\n");
		close(data->tmp_fd);
	}
	if (i == data->groupc - 1)
	{
		ft_printf_fd(STDERR_FILENO, "closing fd[READ]\n");
		close(fd[READ]);
	}
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

	ft_printf_fd(STDERR_FILENO, "======in child_cmd=======\n");
	ft_printf_fd(STDERR_FILENO, "i: %d, in child_cmd cmd: %s\n", i, data->group[i].full_cmd[0]);
	if (!infiles(data, &data->group[i]) && i > 0)
	{
		ft_printf_fd(STDERR_FILENO, "Dupping tmp_fd (%d) to STDIN\n", data->tmp_fd);
		dup2(data->tmp_fd, STDIN_FILENO);
	}
	ft_printf_fd(STDERR_FILENO, "data->group[i]: %p\n", data->group[i]);
	ft_printf_fd(STDERR_FILENO, "data->group[0]: %p\n", data->group[0]);
	ft_printf_fd(STDERR_FILENO, "data->group[1]: %p\n", data->group[1]);
	if (!outfiles(data, &data->group[i]) && i != data->groupc - 1)
	{
		ft_printf_fd(STDERR_FILENO, "Dupping fd[WRITE] to STDOUT\n");
		dup2(fd[READ + 1], STDOUT_FILENO);
	}
	close_fds(data, i, fd);
	if (builtin_check(data, &data->group[i]) == true)
	{
		ft_printf_fd(STDERR_FILENO, "Builtin in child process\n");
		if (!data->group[i].builtin)
			display_error(data, "builtin fucked?", true);
		data->group[i].builtin(data, &data->group[i]);
		return ;
	}
	env = env_2darr(data, data->envp_head);
	// for(int randomcountingvariable = 0; data->group[i].full_cmd[randomcountingvariable]; randomcountingvariable++)
	// 	ft_printf_fd(STDERR_FILENO, "%s\n", data->group[i].full_cmd[randomcountingvariable]);
	path = find_path(data, data->group[i].full_cmd[0]);
	if (!path)
		return (display_error(data, NULL, true));
	// for(int randomcountingvariable = 0; data->group[i].full_cmd[randomcountingvariable]; randomcountingvariable++)
	// 	ft_printf_fd(STDERR_FILENO, "%s\n", data->group[i].full_cmd[randomcountingvariable]);
	ft_printf_fd(STDERR_FILENO, "before execv\n");
	// free_fds();
	// char	line[1000];
	// read(fd[READ], line, 1000);
	ft_printf_fd(STDERR_FILENO, "%s\n", path);
	for(int randomcountingvariable = 0; data->group[i].full_cmd[randomcountingvariable]; randomcountingvariable++)
		ft_printf_fd(STDERR_FILENO, "%s\n", data->group[i].full_cmd[randomcountingvariable]);
	// usleep(50000000);
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
	ft_printf_fd(STDERR_FILENO, "start exec_cmds\n");
	if (data->groupc == 1 && builtin_check(data, data->group))
	{
		ft_printf_fd(STDERR_FILENO, "==================\nbuiltin not in child process\n");
		infiles(data, data->group);
		outfiles(data, data->group);
		ft_printf_fd(STDERR_FILENO, "before function pointer\n");
		data->group[0].builtin(data, &data->group[0]);
		ft_printf_fd(STDERR_FILENO, "after function pointer\n");
		return ;
	}
	ft_printf_fd(STDERR_FILENO, "after builtin parent if\n");
	while (i < (size_t)data->groupc)
	{
		ft_printf_fd(STDERR_FILENO, "parent start\n");
		pipe(fd);
		pid = fork();
		if (pid == -1)
			display_error(data, "fork failed", true);
		if (pid == 0)
			child_cmd(data, i, fd);
		waitpid(pid, NULL, 0); //parent too slow lol
		if (i > 0)
			close(data->tmp_fd);
		data->tmp_fd = fd[READ];
		close(fd[WRITE]);
		ft_printf_fd(STDERR_FILENO, "parent end\n");
		i++;
	}
	ft_printf_fd(STDERR_FILENO, "end\n");
	close(fd[READ]);
}

void	execution(t_data *data)
{
	size_t	i;
	// int32_t	status;

	i = 0;
	//ft_printf_fd(STDERR_FILENO, "my leg hurts\n");
	exec_cmds(data);
	ft_printf_fd(STDERR_FILENO, "after exec_cmds\n");
	// while (i < data->groupc)
	// {
	// 	// wait(&status);
	// 	waitpid(-1, &status, WNOHANG);
	// 	data->status = status;
	// 	i++;
	// }
	free_at_exit(data);
}
