/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:48:19 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/28 20:12:19 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	builtin_check(t_data *data, t_group *group)
{
	(void)data;
	if (!group || !group->full_cmd || !group->full_cmd[0])
		return (false);
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
			group->builtin = &export;
		else
			group->builtin = &export_add;
	}
	else if (ft_strcmp(group->full_cmd[0], "pwd") == 0)
		group->builtin = &pwd;
	else if (ft_strcmp(group->full_cmd[0], "unset") == 0)
		group->builtin = &unset;
	if (group && group->builtin)
		return (true);
	return (false);
}

/**
 * First I find the correct path for the next command in find_path()
 * Execve will execute another program which takes over the entire process.
 * Which is why this is done in a child process. 
 * At the very last iteration, the output is redirected to a file. 
 */
static int32_t	child_cmd(t_data *data, size_t i, int32_t fd[2])
{
	char	*path;
	char	**env;

	path = NULL;
	if (!infiles(data, &data->group[i], NULL) && i > 0)
		dup2(data->tmp_fd, STDIN_FILENO);
	if (!outfiles(data, &data->group[i], NULL) && i != data->groupc - 1)
		dup2(fd[WRITE], STDOUT_FILENO);
	close_fds(data, i, fd);
	if (builtin_check(data, &data->group[i]) == true)
	{
		g_exitcode = data->group[i].builtin(data, &data->group[i]);
		exit(g_exitcode);
	}
	if (data->group[i].full_cmd)
		path = find_path(data, data->group[i].full_cmd[0]);
	if (!path)
		return (display_error(CMD, join_err(data->group[i].full_cmd[0], \
												NULL), NULL, NULL), 127);
	if (!data->group[i].full_cmd)
		exit(0);
	env = env_2darr(data, data->envp_head);
	if (execve(path, data->group[i].full_cmd, env) == -1)
		return (free_2d(env), ft_perror(data->group[i].full_cmd[0], NULL), 127);
	return (1);
}

static void	builtin_in_parent(t_data *data)
{
	t_fds	fds;
	bool	infile;
	bool	outfile;

	infile = infiles(data, data->group, &fds);
	outfile = outfiles(data, data->group, &fds);
	g_exitcode = data->group[0].builtin(data, &data->group[0]);
	if (infile != 0)
		dup2(fds.std_in, infile);
	if (outfile != 0)
		dup2(fds.std_out, outfile);
	return ;
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
		return (builtin_in_parent(data));
	while (i < (size_t)data->groupc)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			g_exitcode = child_cmd(data, i, fd);
			if (g_exitcode != 0)
			{
				fprintf(stderr, "hi\n");
				free_data(data);
				exit(g_exitcode);
			}
		}
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
	status = 0;
	if (!data->group)
		return ;
	data->group[0].builtin = NULL;
	signal(SIGINT, SIG_IGN);
	exec_cmds(data);
	if (g_exitcode > 255)
		g_exitcode = g_exitcode % 256;
	while (i < data->groupc && (!(data->groupc == 1 && data->group[0].builtin)))
	{
		waitpid(-1, &status, 0);
		set_exitcode(status);
		i++;
	}
	free_groups(data);
}
