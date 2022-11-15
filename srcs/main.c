/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:07:48 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/15 13:10:46 by pmoghadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

static void	init(t_data *data, char **envp)
{
	ft_bzero(data, sizeof(data));
	env_innit(data, envp);
	path_innit(data);
}

/**
 * WIFSIGNALED indicates that the child process exited because it raised a 
 * signal. 
 * WTERMSIG returns the value of the signal raised by the child process.
 * If SIGINT (interrupt/CTRL-C) was raised, it adds 128 to the exit code.
 */
void	set_exitcode(t_data *data)
{
	if (WIFSIGNALED(data->status))
	{
		if (WTERMSIG(data->status) == SIGINT)
			data->status = 128 + WTERMSIG(data->status);
	}
}

static void	ctrl_c(int32_t sig)
{
	(void)sig;
	ft_printf_fd(STDOUT_FILENO, "\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay(); // not sure if this is fine or not
}

static void	ctrl_bslash(int32_t sig)
{
	(void)sig;
	rl_redisplay();
	signal(SIGQUIT, SIG_IGN);
}

int32_t	main(int32_t argc, char **argv, char **envp)
{
	char	*str;
	t_data	data;

	(void)argc;
	(void)argv;
	init(&data, envp);
	while (69)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, ctrl_bslash);
		signal(SIGQUIT, SIG_IGN);
		str = readline("🦇Mishell: ");
		if (str == NULL)
			return (printf("exit\n"), 0);
		parser(str, envp, &data);
		execution(&data);
		add_history(str);
		free(str);
	}
	// free_data(&data);
	return (0);
}
