/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:07:48 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/23 14:49:55 by pmoghadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

// #ifdef (DEBUG)
void	this_is_debug_yo(void)
{
	ft_printf_fd(STDERR_FILENO, "%s", debugBuf);
}
// #endif

static void	init(t_data *data, char **envp)
{
	ft_bzero(data, sizeof(data));
	data->group = NULL;
	env_innit(data, envp);
	init_oldpwd(data);
	g_exitcode = 0;
}

/**
 * WIFSIGNALED indicates that the child process exited because it raised a 
 * signal. 
 * WTERMSIG returns the value of the signal raised by the child process.
 * If SIGINT (interrupt/CTRL-C) was raised, it adds 128 to the exit code.
 */
void	set_exitcode(int32_t status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			g_exitcode = 128 + WTERMSIG(status);
	}
	else if (WIFEXITED(status))
		g_exitcode = WEXITSTATUS(status);
}

static void	ctrl_c(int32_t sig)
{
	(void)sig;
	ft_printf_fd(STDOUT_FILENO, "\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay(); // not sure if this is fine or not
	g_exitcode = 1;
}

// static void	ctrl_bslash(int32_t sig)
// {
// 	(void)sig;
// 	g_exitcode = 0;
// 	signal(SIGQUIT, SIG_IGN);
// }

void	free_fds(void)
{
	int	i;

	i = 3;
	while (i <= 4096)
		close(i++);
}

void	print_parser(t_data *data)
{
	size_t		i;
	size_t		j;
	t_infile	*infile;
	t_outfile	*outfile;

	i = 0;
	j = 0;
	printf("=====PRINTING PARSER=======\n");
	while (i < data->groupc)
	{
		infile = data->group[i].infile;
		outfile = data->group[i].outfile;
		printf("groupc: %zu\n", data->groupc);
		while (data->group[i].full_cmd[j])
		{
			printf("cmd[%zu]: %s\n", j, data->group[i].full_cmd[j]);
			j++;
		}
		j = 0;
		print_2d_fd(data->group[i].full_cmd, 1);
		while (outfile != NULL)
		{
			printf("outfile name: %s append: %d\n", outfile->name, outfile->append);
			outfile = outfile->next;
		}
		while (infile != NULL)
		{
			printf("infile name: %s here_doc: %d\n", infile->name, infile->here_doc);
			infile = infile->next;
		}
		printf("builtin: %p\n", data->group[i].builtin);
		i++;
	}
	printf("==========================\n");
}


int32_t	main(int32_t argc, char **argv, char **envp)
{
	t_data	data;
	char	*str;

	(void)argc;
	(void)argv;
	init(&data, envp);
	greeting_msg(data.envp_head);
	while (69)
	{
		signal(SIGINT, ctrl_c);
		// signal(SIGQUIT, ctrl_bslash);
		signal(SIGQUIT, SIG_IGN);
		str = readline(PROMPT);
		if (str == NULL)
			return (printf("exit\n"), 0);
		parser(str, data.envp_head, &data);
		// print_parser(&data);
		if (ft_strncmp(str, "?", 1) == 0)
			printf("exit code: %d\n", g_exitcode);
		if (data.group)
			execution(&data);
		add_history(str);
		free(str);
	}
	free_data(&data);
	return (0);
}
