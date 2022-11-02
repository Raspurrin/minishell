/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:07:48 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/02 02:01:07 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

/**
 * 1. export something=blue | env >outfile1
 * 2. << heredoc1 <<heredoc2 grep yo >outfile2 >outfile3
 * 3. <infile1 <<heredoc1 grep yo >outfile4 | <infile2 grep file >outfile5
 * 4. cat | cat | ls >outfile6
 * 5. export something=blue;env >outfile1
 * 6. export something=;env >outfile1;export >outfile2;unset something; export >outfile3
 * 7. export something=====blue;env outfile1;
 * 8. echo -nnn -----nn --nnnnn >outfile1
 * 9. env env env
 * 10. env env hoi
 * 11. unset PWD; env | grep PWD >outfile1
 * 12. /bin/cd ../;pwd
*/
static void	parser(t_data *data, char *test)
{
	if (ft_strncmp("1", test, 1) == 0)
	{
		data->groupc = 2;
		data->group = ft_calloc(sizeof(t_group), 2);
		data->group[0].full_cmd = ft_calloc(3, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("export");
		data->group[0].full_cmd[1] = ft_strdup("something=blue");
		data->group[0].full_cmd[2] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = NULL;
		data->group[0].builtin = NULL;
		data->group[1].full_cmd = ft_calloc(2, sizeof(char *));
		data->group[1].full_cmd[0] = ft_strdup("env");
		data->group[1].full_cmd[1] = NULL;
		data->group[1].outfile = ft_calloc(sizeof(t_outfile), 1);
		data->group[1].outfile->name = ft_strdup(FOLDER1"outfile1");
		data->group[1].outfile->append = false;
		data->group[1].outfile->next = NULL;
		data->group[1].builtin = NULL;
	}
	if (ft_strncmp("2", test, 1) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(3, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("grep");
		data->group[0].full_cmd[1] = ft_strdup("yo");
		data->group[0].full_cmd[2] = NULL;
		data->group[0].infile = malloc(sizeof(t_infile));
		data->group[0].infile->name = ft_strdup(FOLDER2"infile1");
		data->group[0].infile->here_doc = false;
		data->group[0].infile->next = malloc(sizeof(t_infile));
		data->group[0].infile->next->name = ft_strdup(FOLDER2"infile2");
		data->group[0].infile->next->here_doc = false;
		data->group[0].infile->next->next = NULL;
		data->group[0].outfile = malloc(sizeof(t_infile));
		data->group[0].outfile->name = ft_strdup(FOLDER2"outfile1");
		data->group[0].outfile->append = false;
		data->group[0].outfile->next = malloc(sizeof(t_infile));
		data->group[0].outfile->next->name = ft_strdup(FOLDER2"outfile2");
		data->group[0].outfile->next->append = false;
		data->group[0].outfile->next->next = NULL;
	}
	if (ft_strncmp("3", test, 1) == 0)
	{
		data->groupc = 2;
		data->group = ft_calloc(sizeof(t_group), 2);
		data->group[0].full_cmd = ft_calloc(3, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("grep");
		data->group[0].full_cmd[1] = ft_strdup("yo");
		data->group[0].full_cmd[2] = NULL;
		data->group[0].infile = malloc(sizeof(t_infile));
		data->group[0].infile->name = ft_strdup(FOLDER3"infile1");
		data->group[0].infile->here_doc = false;
		data->group[0].infile->next = malloc(sizeof(t_infile));
		data->group[0].infile->next->name = ft_strdup(FOLDER3"infile2");
		data->group[0].infile->next->here_doc = false;
		data->group[0].infile->next->next = NULL;
		data->group[0].outfile = malloc(sizeof(t_infile));
		data->group[0].outfile->name = ft_strdup(FOLDER3"outfile1");
		data->group[0].outfile->append = false;
		data->group[0].outfile->next = NULL;
		data->group[1].full_cmd = ft_calloc(3, sizeof(char *));
		data->group[1].full_cmd[0] = ft_strdup("grep");
		data->group[1].full_cmd[1] = ft_strdup("file");
		data->group[1].full_cmd[2] = NULL;
		data->group[1].infile = malloc(sizeof(t_infile));
		data->group[1].infile->name = ft_strdup(FOLDER3"infile3");
		data->group[1].infile->here_doc = false;
		data->group[1].infile->next = NULL;
		data->group[1].outfile = malloc(sizeof(t_infile));
		data->group[1].outfile->name = ft_strdup(FOLDER3"outfile2");
		data->group[1].outfile->append = false;
		data->group[1].outfile->next = NULL;
	}
	if (ft_strncmp("4", test, 1) == 0)
	{
		data->groupc = 3;
		data->group = ft_calloc(sizeof(t_group), 3);
		data->group[0].full_cmd = ft_calloc(2, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("cat");
		data->group[0].full_cmd[1] = NULL;
		data->group[1].full_cmd = ft_calloc(2, sizeof(char *));
		data->group[1].full_cmd[0] = ft_strdup("cat");
		data->group[1].full_cmd[1] = NULL;
		data->group[2].full_cmd = ft_calloc(2, sizeof(char *));
		data->group[2].full_cmd[0] = ft_strdup("ls");
		data->group[2].full_cmd[1] = NULL;
		data->group[2].outfile = malloc(sizeof(t_outfile));
		data->group[2].outfile->name = ft_strdup(FOLDER4"outfile1");
		data->group[2].outfile->append = false;
		data->group[2].outfile->next = NULL;
	}
	if (ft_strncmp("5", test, 2) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(3, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("export");
		data->group[0].full_cmd[1] = ft_strdup("something=blue");
		data->group[0].full_cmd[2] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = NULL;
		data->group[0].builtin = NULL;
		execution(data);
		parser(data, "5.1");
	}
	if (ft_strncmp("5.1", test, 3) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(2, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("env");
		data->group[0].full_cmd[1] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = malloc(sizeof(t_outfile));
		data->group[0].outfile->name = ft_strdup(FOLDER5"outfile1");
		data->group[0].outfile->append = false;
		data->group[0].outfile->next = NULL;
		data->group[0].builtin = NULL;
		return (execution(data), exit(0));
	}
	if (ft_strncmp("6", test, 3) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(2, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("something=");
		data->group[0].full_cmd[1] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = NULL;
		data->group[0].builtin = NULL;
		execution(data);
		parser(data, "6.1");
	}
	if (ft_strncmp("6.1", test, 3) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(2, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("env");
		data->group[0].full_cmd[1] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = malloc(sizeof(t_outfile));
		data->group[0].outfile->name = ft_strdup(FOLDER6"outfile1");
		data->group[0].outfile->append = false;
		data->group[0].outfile->next = NULL;
		data->group[0].builtin = NULL;
		execution(data);
		parser(data, "6.2");
	}
	if (ft_strncmp("6.2", test, 3) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(2, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("export");
		data->group[0].full_cmd[1] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = malloc(sizeof(t_outfile));
		data->group[0].outfile->name = ft_strdup(FOLDER6"outfile2");
		data->group[0].outfile->append = false;
		data->group[0].outfile->next = NULL;
		data->group[0].builtin = NULL;
		execution(data);
		parser(data, "6.3");
	}
	if (ft_strncmp("6.3", test, 3) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(3, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("unset");
		data->group[0].full_cmd[1] = ft_strdup("something");
		data->group[0].full_cmd[2] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = NULL;
		data->group[0].builtin = NULL;
		execution(data);
		parser(data, "6.4");
	}
	if (ft_strncmp("6.4", test, 3) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(2, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("env");
		data->group[0].full_cmd[1] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = malloc(sizeof(t_outfile));
		data->group[0].outfile->name = ft_strdup(FOLDER6"outfile3");
		data->group[0].outfile->append = false;
		data->group[0].outfile->next = NULL;
		data->group[0].builtin = NULL;
		return (execution(data), exit(0));
	}
	if (ft_strncmp("7", test, 3) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(3, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("export");
		data->group[0].full_cmd[1] = ft_strdup("something=====blue");
		data->group[0].full_cmd[2] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = NULL;
		data->group[0].builtin = NULL;
		execution(data);
		parser(data, "7.1");
	}
	if (ft_strncmp("7.1", test, 3) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(2, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("env");
		data->group[0].full_cmd[1] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = malloc(sizeof(t_outfile));
		data->group[0].outfile->name = ft_strdup(FOLDER7"outfile1");
		data->group[0].outfile->append = false;
		data->group[0].outfile->next = NULL;
		data->group[0].builtin = NULL;
		return (execution(data), exit(0));
	}
	if (ft_strncmp("8", test, 1) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(5, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("echo");
		data->group[0].full_cmd[1] = ft_strdup("-nnn");
		data->group[0].full_cmd[2] = ft_strdup("-----nn");
		data->group[0].full_cmd[3] = ft_strdup("--nnnnn");
		data->group[0].full_cmd[4] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = malloc(sizeof(t_outfile));
		data->group[0].outfile->name = ft_strdup(FOLDER8"outfile1");
		data->group[0].outfile->append = false;
		data->group[0].outfile->next = NULL;
		data->group[0].builtin = NULL;
	}
	if (ft_strncmp("9", test, 1) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(4, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("env");
		data->group[0].full_cmd[1] = ft_strdup("env");
		data->group[0].full_cmd[2] = ft_strdup("env");
		data->group[0].full_cmd[3] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = malloc(sizeof(t_outfile));
		data->group[0].outfile->name = ft_strdup(FOLDER9"outfile1");
		data->group[0].outfile->append = false;
		data->group[0].outfile->next = NULL;
		data->group[0].builtin = NULL;
	}
	if (ft_strncmp("10", test, 2) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(4, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("env");
		data->group[0].full_cmd[1] = ft_strdup("env");
		data->group[0].full_cmd[2] = ft_strdup("hoi");
		data->group[0].full_cmd[3] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = malloc(sizeof(t_outfile));
		data->group[0].outfile->name = ft_strdup(FOLDER10"outfile1");
		data->group[0].outfile->append = false;
		data->group[0].outfile->next = NULL;
		data->group[0].builtin = NULL;
	}
	if (ft_strncmp("11", test, 4) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(3, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("unset");
		data->group[0].full_cmd[1] = ft_strdup("PWD");
		data->group[0].full_cmd[2] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = NULL;
		data->group[0].builtin = NULL;
		execution(data);
		parser(data, "11.1");
	}
	if (ft_strncmp("11.1", test, 4) == 0)
	{
		data->groupc = 2;
		data->group = ft_calloc(sizeof(t_group), 2);
		data->group[0].full_cmd = ft_calloc(2, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("env");
		data->group[0].full_cmd[1] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = NULL;
		data->group[0].builtin = NULL;
		data->group[1].full_cmd = ft_calloc(3, sizeof(char *));
		data->group[1].full_cmd[0] = ft_strdup("grep");
		data->group[1].full_cmd[0] = ft_strdup("PWD");
		data->group[1].full_cmd[1] = NULL;
		data->group[1].outfile = ft_calloc(sizeof(t_outfile), 1);
		data->group[1].outfile->name = ft_strdup(FOLDER11"outfile1");
		data->group[1].outfile->append = false;
		data->group[1].outfile->next = NULL;
		data->group[1].builtin = NULL;
		return (execution(data), exit(0));
	}
	if (ft_strncmp("12", test, 4) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(3, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("/bin/cd");
		data->group[0].full_cmd[1] = ft_strdup("../");
		data->group[0].full_cmd[2] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = NULL;
		data->group[0].builtin = NULL;
		execution(data);
		parser(data, "12.1");
	}
	if (ft_strncmp("12.1", test, 4) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(3, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("grep");
		data->group[0].full_cmd[1] = ft_strdup("PWD");
		data->group[0].full_cmd[2] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = ft_calloc(sizeof(t_outfile), 1);
		data->group[0].outfile->name = ft_strdup(FOLDER12"outfile1");
		data->group[0].outfile->append = false;
		data->group[0].outfile->next = NULL;
		data->group[0].builtin = NULL;
		return (execution(data), exit(0));
	}
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

// static void	ctrl_c(int32_t sig)
// {
// 	(void)sig;
// 	ft_printf_fd(STDOUT_FILENO, "\n");
// 	rl_on_new_line();
// 	rl_replace_line("", 1);
// 	rl_redisplay(); // not sure if this is fine or not
// }

// static void	ctrl_bslash(int32_t sig)
// {
// 	(void)sig;
// 	rl_redisplay();
// 	signal(SIGQUIT, SIG_IGN);
// }

int32_t	main(int32_t argc, char **argv, char **envp)
{
	t_data	data;
	// char	*str;

	(void)argc;
	(void)argv;
	ft_bzero(&data, sizeof(data));
	data.tmp_fd = 0;
	env_innit(&data, envp);
	path_innit(&data);
	(void)parser;
	parser(&data, argv[1]);
	printf("parsing ok\n");
	if (argv[1])
		return (parser(&data, argv[1]), execution(&data), 0);
	// while (69)
	// {
	// 	signal(SIGINT, ctrl_c);
	// 	signal(SIGQUIT, ctrl_bslash);
	// 	signal(SIGQUIT, SIG_IGN);
	// 	str = readline("🦇Mishell: ");
	// 	if (str == NULL)
	// 		return (printf("exit\n"), 0);
		// if (argv[1] == '1')
		// 	return (parser(&data, 1), 0);
		// else if (argv[1] == '2')
		// 	return (parser(&data, 2), 0);
		// else if (argv[2] == '3')
		// 	return (parser(&data, 3), 0);
		// else if (argv[2] == '4')
		// 	return (parser(&data, 4), 0);
		// else if (argv[2] == '5')
		// 	return (parser(&data, 5), 0);
		// if (ft_strncmp("$?", str, 2) == 0)
		// 	ft_printf_fd(STDOUT_FILENO, "exit: %s\n", ft_itoa(data.status));
		// if (ft_strncmp("exec", str, 4) == 0)
		// 	execution(&data);
		// if (ft_strncmp("env", str, 4) == 0)
		// 	print_env(&data, &data.group[0]);
		// if (ft_strncmp("export", str, 4) == 0)
		// 	export(&data, &data.group[1]);
	// 	add_history(str);
	// 	free(str);
	// }
	// free_data(&data);
	return (0);
}
