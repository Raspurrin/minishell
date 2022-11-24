/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:48:19 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/23 01:07:33 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	builtin_check(t_data *data, t_group *group)
{
	(void)data;
	if (!group || !group->full_cmd)
		return (false);
	sprintf(debugBuf + ft_strlen(debugBuf), "in builtlin_check, cmd: %s\n", group->full_cmd[0]);
	if (ft_strcmp(group->full_cmd[0], "cd") == 0)
		group->builtin = &cd;
	else if (ft_strcmp(group->full_cmd[0], "echo") == 0)
		group->builtin = &echo;
	else if (ft_strcmp(group->full_cmd[0], "env") == 0)
		group->builtin = &env;
	else if (ft_strcmp(group->full_cmd[0], "exit") == 0)
		group->builtin = &exit_check;
	else if (ft_strcmp(group->full_cmd[0], "export") == 0) 
	{
		if (group->full_cmd[1] == NULL)
		{
			sprintf(debugBuf + ft_strlen(debugBuf), "group->full_cmd[1]: %p builtin is export\n", group->full_cmd[1]);
			group->builtin = &export;
		}
		else
		{
			sprintf(debugBuf + ft_strlen(debugBuf), "group->full_cmd[1]: %p builtin is export_add\n", group->full_cmd[1]);
			group->builtin = &export_add;
		}
	}
	else if (ft_strcmp(group->full_cmd[0], "pwd") == 0)
		group->builtin = &pwd;
	else if (ft_strcmp(group->full_cmd[0], "unset") == 0)
		group->builtin = &unset;
	else
		return (sprintf(debugBuf + ft_strlen(debugBuf), "no builtin found: %p\n", group->builtin), false);
	sprintf(debugBuf + ft_strlen(debugBuf), "group->builtin: %p\n", group->builtin);
	return (true);
}

static void	close_fds(t_data *data, size_t i, int32_t fd[2])
{
	sprintf(debugBuf + ft_strlen(debugBuf), "closing fd[WRITE] (%d)\n", fd[WRITE]);
	close(fd[WRITE]);
	if (i > 0)
	{
		sprintf(debugBuf + ft_strlen(debugBuf), "closing data->tmp_fd (%d)\n", data->tmp_fd);
		close(data->tmp_fd);
	}
	if (i == data->groupc - 1)
	{
		sprintf(debugBuf + ft_strlen(debugBuf), "closing fd[READ] (%d)\n", fd[READ]);
		close(fd[READ]);
	}
}

/**
 * First I find the correct path for the next command in find_path()
 * Execve will execute another program which takes over the entire process.
 * Which is why this is done in a child process. 
 * At the very last itteration, the output is redirected to a file. 
 */
static int32_t	child_cmd(t_data *data, size_t i, int32_t fd[2])
{
	char	*path;
	char	**env;

	path = NULL;
	sprintf(debugBuf + ft_strlen(debugBuf), "======in child_cmd=======\n");
	if (data->group[i].full_cmd)
		sprintf(debugBuf + ft_strlen(debugBuf), "i: %zu, in child_cmd cmd: %s\n", i, data->group[i].full_cmd[0]);
	if (!infiles(data, &data->group[i]) && i > 0)
	{
		sprintf(debugBuf + ft_strlen(debugBuf), "Dupping tmp_fd (%d) to STDIN\n", data->tmp_fd);
		dup2(data->tmp_fd, STDIN_FILENO);
	}
	if (!outfiles(data, &data->group[i]) && i != data->groupc - 1)
	{
		sprintf(debugBuf + ft_strlen(debugBuf), "Dupping fd[WRITE] (%d) to STDOUT\n", fd[WRITE]);
		dup2(fd[WRITE], STDOUT_FILENO);
	}
	close_fds(data, i, fd);
	if (builtin_check(data, &data->group[i]) == true)
	{
		sprintf(debugBuf + ft_strlen(debugBuf), "Builtin in child process\n");
		g_exitcode = data->group[i].builtin(data, &data->group[i]);
		exit(g_exitcode);
	}
	env = env_2darr(data, data->envp_head);
	if (data->group[i].full_cmd)
		path = find_path(data, data->group[i].full_cmd[0]);
	this_is_debug_yo();
	sprintf(debugBuf + ft_strlen(debugBuf), "path: %s\n", path);
	if (!path)
		return (display_error(CMD, join_err(data->group[i].full_cmd[0], NULL), NULL, NULL), 127);
	sprintf(debugBuf + ft_strlen(debugBuf), "before execv\n");
	sprintf(debugBuf + ft_strlen(debugBuf), "%s\n", path);
	if (execve(path, data->group[i].full_cmd, env) == -1)
		return (free(env), ft_perror(data->group[i].full_cmd[0], NULL), 127);
	return (1);
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
	int32_t	status;

	i = 0;
	sprintf(debugBuf + ft_strlen(debugBuf), "start exec_cmd\n");
	if (data->groupc == 1 && builtin_check(data, data->group))
	{
		sprintf(debugBuf + ft_strlen(debugBuf), "==================\nbuiltin not in child process\n");
		infiles(data, data->group);
		outfiles(data, data->group);
		sprintf(debugBuf + ft_strlen(debugBuf), "before function pointer\n");
		g_exitcode = data->group[0].builtin(data, &data->group[0]);
		sprintf(debugBuf + ft_strlen(debugBuf), "after function pointer\n");
		return ;
	}
	sprintf(debugBuf + ft_strlen(debugBuf), "after builtin parent if\n");
	while (i < (size_t)data->groupc)
	{
		sprintf(debugBuf + ft_strlen(debugBuf), "parent start i: %zu\n", i);
		pipe(fd);
		pid = fork();
		// if (pid == -1)
		// 	display_error(data, "fork failed", true);
		sprintf(debugBuf + ft_strlen(debugBuf), "forked\n");
		if (pid == 0)
		{
			ft_printf_fd(STDERR_FILENO, "g_exitcode before child_cmd in child: %d\n", g_exitcode);
			g_exitcode = child_cmd(data, i, fd);
			ft_printf_fd(STDERR_FILENO, "g_exitcode after child_cmd in child: %d\n", g_exitcode);
			if (g_exitcode != 0)
				exit(g_exitcode);
		}
		waitpid(pid, &status, 0); //parent too slow lol
		set_exitcode(status);
		if (i > 0)
		{
			sprintf(debugBuf + ft_strlen(debugBuf), "closing tmp_fd (%d)\n", data->tmp_fd);
			close(data->tmp_fd);
		}
		sprintf(debugBuf + ft_strlen(debugBuf), "saving fd[READ] (%d) into tmp_fd\n", fd[READ]);
		data->tmp_fd = fd[READ];
		close(fd[WRITE]);
		sprintf(debugBuf + ft_strlen(debugBuf), "parent end i: %zu\n", i);
		i++;
	}
	sprintf(debugBuf + ft_strlen(debugBuf), "closing fd[READ]\n");
	close(fd[READ]);
}

void	execution(t_data *data)
{
	size_t	i;
	// int32_t	status;

	i = 0;
	if (!data->group)
		return ;
	signal(SIGINT, SIG_IGN);
	exec_cmds(data);
	sprintf(debugBuf + ft_strlen(debugBuf), "after exec_cmds\n");
	if (g_exitcode > 255)
		g_exitcode = g_exitcode % 256;
	// while (i < data->groupc)
	// {
	// 	waitpid(-1, &status, NULL);
	// 	g_exitcode = status;
	// 	i++;
	// }
	free_groups(data);
}
