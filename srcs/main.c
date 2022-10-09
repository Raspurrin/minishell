/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:07:48 by mialbert          #+#    #+#             */
/*   Updated: 2022/10/09 02:24:13 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

// just for testing purposes
static void	parser(t_data *data)
{
	data->groupc = 2;
	data->group = malloc(sizeof(t_group) * 2);
	data->group[0].full_cmd = ft_calloc(3, sizeof(char *));
	data->group[0].full_cmd[0] = ft_strdup("cd");
	data->group[0].full_cmd[1] = ft_strdup("../");
	data->group[0].full_cmd[2] = NULL;
	data->group[0].infile = malloc(sizeof(t_infile *) * 3);
	data->group[0].infile[0].name = "file1";
	data->group[0].infile[1].name = "file2";
	data->group[0].infilec = 2;
	// data->group[0].infile[2] = NULL;

	data->group[0].outfile = malloc(sizeof(t_outfile *) * 2);
	data->group[0].outfile[0].name = "outfile1";
	data->group[0].outfile[1].name = "outfile2";
	data->group[0].outfilec = 2;
	data->group[0].builtin = false;

	data->group[1].full_cmd = malloc(sizeof(char *) * 2);
	data->group[1].full_cmd[0] = ft_strdup("echo");
	data->group[1].full_cmd[1] = ft_strdup("Heyo Winny the Pooneh");
	data->group[1].full_cmd[2] = NULL;

	data->group[1].infile = malloc(sizeof(t_infile *) * 2);
	data->group[1].infile[0].name = "infile1";
	data->group[1].infilec = 1;
	// data->group[1].infile[1].name = "infile2";

	data->group[1].outfile = malloc(sizeof(t_outfile *) * 2);
	data->group[1].outfile[0].name = "outfile3";
	data->group[1].outfile[1].name = "outfile4";
	data->group[1].outfilec = 2;
	data->group[1].builtin = false;

	data->group[2].full_cmd = malloc(sizeof(char *) * 2);
	data->group[2].full_cmd[0] = ft_strdup("export");
	data->group[2].full_cmd[1] = NULL;

	data->group[3].full_cmd = malloc(sizeof(char *) * 2);
	data->group[3].full_cmd[0] = ft_strdup("export");
	data->group[3].full_cmd[1] = ft_strdup("something=blue");
	data->group[3].full_cmd[2] = NULL;

	data->group[4].full_cmd = malloc(sizeof(char *) * 2);
	data->group[4].full_cmd[0] = ft_strdup("env");
	data->group[4].full_cmd[1] = NULL;

	data->group[5].full_cmd = malloc(sizeof(char *) * 2);
	data->group[5].full_cmd[0] = ft_strdup("unset");
	data->group[5].full_cmd[1] = ft_strdup("USER");
	data->group[5].full_cmd[2] = NULL;

	data->group[6].full_cmd = malloc(sizeof(char *) * 2);
	data->group[6].full_cmd[0] = ft_strdup("export");
	data->group[6].full_cmd[1] = ft_strdup("something123=red");
	data->group[6].full_cmd[2] = NULL;
}

// static void	ctrl_c(int32_t sig)
// {
// 	(void)sig;
// 	// printf("test");
// 	// write(STDIN_FILENO, "", 0);
// 	rl_on_new_line();
// 	// rl_redisplay();
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
	init(&data, envp);
	parser(&data);
	export_add(&data, &data.group[3]);
	export_add(&data, &data.group[6]);
	print_env(&data, data.group);
	// pwd(&data, data.group);
	// printf("%s", get_path(&data));
	// unset(&data, &data.group[5]);
	export(&data, &data.group[2]);

	// print_env(&data, &data.group[3]);
	// export(&data, &data.group[2]);
	// while (69)
	// {
	// 	// signal(SIGINT, ctrl_c);
	// 	// signal(SIGQUIT, ctrl_bslash);
	// 	// signal(SIGQUIT, SIG_IGN);
		// str = readline("🦇Mishell: ");
		// if (str == NULL)
		// 	break ;
	// 	add_history(str);
		// if (ft_strncmp(str, "pwd", 3) == 0) // added these just for testing sake, dw they not stayin' xd 
		// 	pwd(&data, data.group);
		// if (ft_strncmp(str, "cd", 2) == 0)
		// 	cd(&data, &data.group[0]);
		// if (ft_strncmp(str, "echo", 4) == 0)
		// 	echo(&data, &data.group[1]);
		// if (ft_strncmp(str, "export", 6) == 0)
		// 	export(&data, &data.group[2]);
		// if (ft_strncmp(str, "export2", 7) == 0)
		// 	export_add(&data, &data.group[3]);
		// if (ft_strncmp(str, "env", 3) == 0)
		// 	print_env(&data, &data.group[4]);
		// if (ft_strncmp(str, "unset", 5) == 0)
		// 	unset(&data, &data.group[5]);
		// exit_check(&data, data.group);
		// execution(&data);
		// free(str);
	// }
	return (0);
}
