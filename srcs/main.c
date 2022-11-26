/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:07:48 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/25 19:26:00 by pmoghadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

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
	rl_redisplay();
	g_exitcode = 1;
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
		signal(SIGQUIT, SIG_IGN);
		str = readline(PROMPT);
		if (str == NULL)
			return (printf("exit\n"), free_data(&data), 0);
		parser(str, data.envp_head, &data);
		if (data.group)
			execution(&data);
		add_history(str);
		free(str);
	}
	free_data(&data);
	return (0);
}
