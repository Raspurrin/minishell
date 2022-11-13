/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:07:48 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/13 06:50:54 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

/**
 * 1. export something=blue | env >outfile1
 * 2. < infile1 < infile2 grep yo >outfile2 >outfile3
 * 3. <infile1 <<heredoc1 grep yo >outfile4 | <infile2 grep file >outfile5
 * 4. cat | cat | ls >outfile6
 * 5. export something=blue;env >outfile1
 * 6. export something=;env >outfile1;export >outfile2;unset something; export >outfile3
 * 7. export something=====blue;env outfile1;
 * 8. echo -nnn -----nn --nnnnn >outfile1
 * 9. env env env
 * 10. env env hoi
 * 11. unset USER; env | grep USER >outfile1
 * 12. /bin/cd ../;pwd
 * 13. cat
 * 14. cat | cat
 * 15. export > outfile1
 * 16. export > outfile1
 * 17. export > outfile1; export > outfile2
 * 18. export something=blue hallo yo= somethingggg=bbblue hdsrtghsrdghs=ugood? something=red hoi; export > outfile1
 * 19. unset USER; export > outfile1;
 * 20. unset PWD; cd ../; pwd >outfile1; bin/ls >outfile2
 * 21. cd ../minishell/libs; pwd > outfile1; env | grep PWD > outfile2
 * 22. ./minishell; ./minishell; env | grep SHLVL > outfile1; exit; pwd >outfile2
 * 23. echo "yo what is up\n yo yo yo" | grep "yo" > outfile1
 * 24. echo hola | cat | cat | grep hola >outfile1
 * 25. cd /Users/mialbert/Documents; /bin/pwd > outfile1
 * 26. bin/ls; echo $? > outfile1
 * 27. << heredoc1 << heredoc2 grep yo >outfile1
 * 28. << heredoc1 << heredoc2 env >outfile1
*/
static void	fake_parser(t_data *data, char *test)
{
	if (ft_strncmp("1", test, 2) == 0)
	{
		data->groupc = 2;
		data->group = ft_calloc(sizeof(t_group), 2);
		data->group[0].full_cmd = ft_calloc(3, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("export");
		data->group[0].full_cmd[1] = ft_strdup("aaaaa=blue");
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
	else if (ft_strncmp("2", test, 2) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(3, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("grep");
		data->group[0].full_cmd[1] = ft_strdup("yo");
		data->group[0].full_cmd[2] = NULL;
		data->group[0].infile = malloc(sizeof(t_infile));
		data->group[0].infile->name = ft_strdup(FOLDER"infile1");
		data->group[0].infile->here_doc = false;
		data->group[0].infile->next = malloc(sizeof(t_infile));
		data->group[0].infile->next->name = ft_strdup(FOLDER"infile2");
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
	else if (ft_strncmp("3", test, 1) == 0)
	{
		data->groupc = 2;
		data->group = ft_calloc(sizeof(t_group), 2);
		ft_printf_fd(STDERR_FILENO, "data->group[0]: %p\n", data->group[0]);
		ft_printf_fd(STDERR_FILENO, "data->group[1]: %p\n", data->group[1]);
		data->group[0].full_cmd = ft_calloc(3, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("grep");
		data->group[0].full_cmd[1] = ft_strdup("yo");
		data->group[0].full_cmd[2] = NULL;
		data->group[0].infile = malloc(sizeof(t_infile));
		data->group[0].infile->name = ft_strdup(FOLDER"infile1");
		data->group[0].infile->here_doc = false;
		data->group[0].infile->next = malloc(sizeof(t_infile));
		data->group[0].infile->next->name = ft_strdup(FOLDER"infile2");
		data->group[0].infile->next->here_doc = false;
		data->group[0].infile->next->next = NULL;
		data->group[0].outfile = malloc(sizeof(t_outfile));
		data->group[0].outfile->name = ft_strdup(FOLDER3"outfile1");
		data->group[0].outfile->append = false;
		data->group[0].outfile->next = NULL;
		data->group[0].builtin = NULL;
		data->group[1].full_cmd = ft_calloc(3, sizeof(char *));
		data->group[1].full_cmd[0] = ft_strdup("grep");
		data->group[1].full_cmd[1] = ft_strdup("file");
		data->group[1].full_cmd[2] = NULL;
		data->group[1].infile = malloc(sizeof(t_infile));
		data->group[1].infile->name = ft_strdup("infile3");
		data->group[1].infile->here_doc = false;
		data->group[1].infile->next = NULL;
		data->group[1].outfile = malloc(sizeof(t_outfile));
		ft_printf_fd(STDERR_FILENO, "(this is the memory location we are looking for lol): %p\n", &data->group[1].outfile);
		data->group[1].outfile->name = ft_strdup(FOLDER3"outfile2");
		data->group[1].outfile->append = false;
		data->group[1].outfile->next = NULL;
		data->group[1].builtin = NULL;
		ft_printf_fd(STDERR_FILENO, "data->group[0]: %p\n", data->group[0]);
		ft_printf_fd(STDERR_FILENO, "data->group[1]: %p\n", data->group[1]);
	}
	else if (ft_strncmp("4", test, 1) == 0)
	{
		data->groupc = 2;
		data->group = ft_calloc(sizeof(t_group), 2);
		data->group[0].full_cmd = ft_calloc(2, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("cat");
		data->group[0].full_cmd[1] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = NULL;
		data->group[0].builtin = NULL;
		data->group[1].full_cmd = ft_calloc(2, sizeof(char *));
		data->group[1].full_cmd[0] = ft_strdup("ls");
		data->group[1].full_cmd[1] = NULL;
		data->group[1].infile = NULL;
		data->group[1].outfile = malloc(sizeof(t_infile));
		data->group[1].outfile->name = ft_strdup(FOLDER4"outfile1");
		data->group[1].outfile->append = false;
		data->group[1].outfile->next = NULL;
		data->group[1].builtin = NULL;
	}
	else if (ft_strncmp("5", test, 2) == 0)
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
		free_groups(data);
		fake_parser(data, "5.1");
	}
	else if (ft_strncmp("5.1", test, 3) == 0)
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
		return (execution(data), free_data(data), exit(0));
	}
	else if (ft_strncmp("6", test, 3) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(3, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("export");
		data->group[0].full_cmd[1] = ft_strdup("something=");
		data->group[0].full_cmd[2] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = NULL;
		data->group[0].builtin = NULL;
		execution(data);
		free_groups(data);
		fake_parser(data, "6.1");
	}
	else if (ft_strncmp("6.1", test, 3) == 0)
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
		free_groups(data);
		fake_parser(data, "6.2");
	}
	else if (ft_strncmp("6.2", test, 3) == 0)
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
		free_groups(data);
		fake_parser(data, "6.3");
	}
	else if (ft_strncmp("6.3", test, 3) == 0)
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
		return (execution(data), free_data(data), exit(0));
	}
	// if (ft_strncmp("6.4", test, 3) == 0)
	// {
	// 	data->groupc = 1;
	// 	data->group = ft_calloc(sizeof(t_group), 1);
	// 	data->group[0].full_cmd = ft_calloc(2, sizeof(char *));
	// 	data->group[0].full_cmd[0] = ft_strdup("export");
	// 	data->group[0].full_cmd[1] = NULL;
	// 	data->group[0].infile = NULL;
	// 	data->group[0].outfile = malloc(sizeof(t_outfile));
	// 	data->group[0].outfile->name = ft_strdup(FOLDER6"outfile3");
	// 	data->group[0].outfile->append = false;
	// 	data->group[0].outfile->next = NULL;
	// 	data->group[0].builtin = NULL;
	// 	export(data, &data->group[0]);
	// 	return (execution(data), free_data(data), exit(0));
	// }
	else if (ft_strncmp("7", test, 3) == 0)
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
		free_groups(data);
		fake_parser(data, "7.1");
	}
	else if (ft_strncmp("7.1", test, 3) == 0)
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
	else if (ft_strncmp("8", test, 1) == 0)
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
	else if (ft_strncmp("9", test, 1) == 0)
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
	else if (ft_strncmp("10", test, 2) == 0)
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
	else if (ft_strncmp("11", test, 4) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(3, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("unset");
		data->group[0].full_cmd[1] = ft_strdup("XPC_FLAGS");
		data->group[0].full_cmd[2] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = NULL;
		data->group[0].builtin = NULL;
		execution(data);
		free_groups(data);
		fake_parser(data, "11.1");
	}
	else if (ft_strncmp("11.1", test, 4) == 0)
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
		data->group[1].full_cmd[1] = ft_strdup("XPC");
		data->group[1].full_cmd[2] = NULL;
		data->group[1].outfile = ft_calloc(sizeof(t_outfile), 1);
		data->group[1].outfile->name = ft_strdup(FOLDER11"outfile1");
		data->group[1].outfile->append = !true;
		data->group[1].outfile->next = NULL;
		data->group[1].builtin = NULL;
		return (execution(data), exit(0));
	}
	else if (ft_strncmp("12", test, 4) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(3, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("usr/bin/cd");
		data->group[0].full_cmd[1] = ft_strdup("../");
		data->group[0].full_cmd[2] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = NULL;
		data->group[0].builtin = NULL;
		execution(data);
		free_groups(data);
		fake_parser(data, "12.1");
	}
	else if (ft_strncmp("12.1", test, 4) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(3, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("pwd");
		data->group[0].full_cmd[1] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = ft_calloc(sizeof(t_outfile), 1);
		data->group[0].outfile->name = ft_strdup(FOLDER12"outfile1");
		data->group[0].outfile->append = false;
		data->group[0].outfile->next = NULL;
		data->group[0].builtin = NULL;
		return (execution(data), exit(0));
	}
	else if (ft_strncmp("13", test, 2) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(2, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("cat");
		data->group[0].full_cmd[1] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = NULL;
		data->group[0].builtin = NULL;
	}
	else if (ft_strncmp("14", test, 4) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(2, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("cat");
		data->group[0].full_cmd[1] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = NULL;
		data->group[0].builtin = NULL;
		execution(data);
		free_groups(data);
		fake_parser(data, "14.2");
	}
	else if (ft_strncmp("14.2", test, 4) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(2, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("cat");
		data->group[0].full_cmd[1] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = NULL;
		data->group[0].builtin = NULL;
		return (execution(data), exit(0));
	}
	else if (ft_strncmp("15", test, 2) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(2, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("./minishell");
		data->group[0].full_cmd[1] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = NULL;
		data->group[0].builtin = NULL;
	}
	else if (ft_strncmp("16", test, 2) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(2, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("export");
		data->group[0].full_cmd[1] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = ft_calloc(sizeof(t_outfile), 1);
		data->group[0].outfile->name = ft_strdup("minishell_tester/test16/outfile1");
		data->group[0].outfile->append = false;
		data->group[0].outfile->next = NULL;
		data->group[0].builtin = NULL;
	}
	else if (ft_strncmp("17", test, 4) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(2, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("export");
		data->group[0].full_cmd[1] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = ft_calloc(sizeof(t_outfile), 1);
		data->group[0].outfile->name = ft_strdup("minishell_tester/test17/outfile1");
		data->group[0].outfile->append = false;
		data->group[0].outfile->next = NULL;
		data->group[0].builtin = NULL;
		execution(data);
		free_groups(data);
		fake_parser(data, "17.1");
	}
	else if (ft_strncmp("17.1", test, 4) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(2, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("export");
		data->group[0].full_cmd[1] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = ft_calloc(sizeof(t_outfile), 1);
		data->group[0].outfile->name = ft_strdup("minishell_tester/test17/outfile2");
		data->group[0].outfile->append = false;
		data->group[0].outfile->next = NULL;
		data->group[0].builtin = NULL;
		return (execution(data), exit(0));
	}
		else if (ft_strncmp("18", test, 4) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(9, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("export");
		data->group[0].full_cmd[1] = ft_strdup("something=blue");
		data->group[0].full_cmd[2] = ft_strdup("hallo");
		data->group[0].full_cmd[3] = ft_strdup("yo=");
		data->group[0].full_cmd[4] = ft_strdup("somethingggg=bbblue");
		data->group[0].full_cmd[5] = ft_strdup("hdsrtghsrdghs=ugood?");
		data->group[0].full_cmd[6] = ft_strdup("something=red");
		data->group[0].full_cmd[7] = ft_strdup("hoi");
		data->group[0].full_cmd[8] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = NULL;
		data->group[0].builtin = NULL;
		execution(data);
		free_groups(data);
		fake_parser(data, "18.1");
	}
	else if (ft_strncmp("18.1", test, 4) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(2, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("export");
		data->group[0].full_cmd[1] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = malloc(sizeof(t_outfile));
		data->group[0].outfile->name = ft_strdup("minishell_tester/test18/outfile1");
		data->group[0].outfile->append = false;
		data->group[0].outfile->next = NULL;
		data->group[0].builtin = NULL;
		return (execution(data), free_data(data), exit(0));
	}
	else if (ft_strncmp("19", test, 4) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(3, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("unset");
		data->group[0].full_cmd[1] = ft_strdup("USER");
		data->group[0].full_cmd[2] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = NULL;
		data->group[0].builtin = NULL;
		execution(data);
		free_groups(data);
		fake_parser(data, "19.1");
	}
	else if (ft_strncmp("19.1", test, 4) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(2, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("export");
		data->group[0].full_cmd[1] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = malloc(sizeof(t_outfile));
		data->group[0].outfile->name = ft_strdup("minishell_tester/test19/outfile1");
		data->group[0].outfile->append = false;
		data->group[0].outfile->next = NULL;
		data->group[0].builtin = NULL;
		return (execution(data), free_data(data), exit(0));
	}
	else if (ft_strncmp("20", test, 4) == 0)
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
		free_groups(data);
		fake_parser(data, "20.1");
	}
	else if (ft_strncmp("20.1", test, 4) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(3, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("cd");
		data->group[0].full_cmd[1] = ft_strdup("../");
		data->group[0].full_cmd[2] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = NULL;
		data->group[0].builtin = NULL;
		execution(data);
		free_groups(data);
		fake_parser(data, "20.2");
	}
	else if (ft_strncmp("20.2", test, 4) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(2, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("pwd");
		data->group[0].full_cmd[1] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = malloc(sizeof(t_outfile));
		data->group[0].outfile->name = ft_strdup("minishell_tester/test20/outfile1");
		data->group[0].outfile->append = false;
		data->group[0].outfile->next = NULL;
		data->group[0].builtin = NULL;
		execution(data);
		free_groups(data);
		fake_parser(data, "20.3");
	}
	else if (ft_strncmp("20.3", test, 4) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(2, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("/bin/ls");
		data->group[0].full_cmd[1] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = malloc(sizeof(t_outfile));
		data->group[0].outfile->name = ft_strdup("minishell_tester/test20/outfile2");
		data->group[0].outfile->append = false;
		data->group[0].outfile->next = NULL;
		data->group[0].builtin = NULL;
		return (execution(data), free_data(data), exit(0));
	}
	else if (ft_strncmp("21", test, 4) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(3, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("cd");
		data->group[0].full_cmd[1] = ft_strdup("../minishell/libs");
		data->group[0].full_cmd[2] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = NULL;
		data->group[0].builtin = NULL;
		execution(data);
		free_groups(data);
		fake_parser(data, "21.1");
	}
	else if (ft_strncmp("21.1", test, 4) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(3, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("pwd");
		data->group[0].full_cmd[1] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = malloc(sizeof(t_outfile));
		data->group[0].outfile->name = ft_strdup("minishell_tester/test21/outfile1");
		data->group[0].outfile->append = false;
		data->group[0].outfile->next = NULL;
		data->group[0].builtin = NULL;
		execution(data);
		free_groups(data);
		fake_parser(data, "21.2");
	}
	else if (ft_strncmp("21.2", test, 4) == 0)
	{
		data->groupc = 2;
		data->group = ft_calloc(sizeof(t_group), 2);
		data->group[0].full_cmd = ft_calloc(2, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("env");
		data->group[0].full_cmd[1] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = malloc(sizeof(t_outfile));
		data->group[0].outfile = NULL;
		data->group[0].builtin = NULL;
		data->group[1].full_cmd = ft_calloc(3, sizeof(char *));
		data->group[1].full_cmd[0] = ft_strdup("grep");
		data->group[1].full_cmd[1] = ft_strdup("PWD");
		data->group[1].full_cmd[2] = NULL;
		data->group[1].infile = NULL;
		data->group[1].outfile = malloc(sizeof(t_outfile));
		data->group[1].outfile->name = ft_strdup("minishell_tester/test21/outfile2");
		data->group[1].outfile->append = false;
		data->group[1].outfile->next = NULL;
		data->group[1].builtin = NULL;
		return (execution(data), free_data(data), exit(0));
	}
	else if (ft_strncmp("22", test, 4) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(3, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("./minishell");
		data->group[0].full_cmd[1] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = NULL;
		data->group[0].builtin = NULL;
		execution(data);
		free_groups(data);
		fake_parser(data, "22.1");
	}
	else if (ft_strncmp("22.1", test, 4) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(3, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("./minishell");
		data->group[0].full_cmd[1] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = NULL;
		data->group[0].builtin = NULL;
		execution(data);
		free_groups(data);
		fake_parser(data, "22.2");
	}
	else if (ft_strncmp("22.2", test, 4) == 0)
	{
		data->groupc = 2;
		data->group = ft_calloc(sizeof(t_group), 2);
		data->group[0].full_cmd = ft_calloc(3, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("env");
		data->group[0].full_cmd[1] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = NULL;
		data->group[0].builtin = NULL;
		data->group[1].full_cmd = ft_calloc(3, sizeof(char *));
		data->group[1].full_cmd[0] = ft_strdup("grep");
		data->group[1].full_cmd[1] = ft_strdup("SHLVL");
		data->group[1].full_cmd[2] = NULL;
		data->group[1].infile = NULL;
		data->group[1].outfile = malloc(sizeof(t_outfile));
		data->group[1].outfile->name = ft_strdup("minishell_tester/test22/outfile1");
		data->group[1].outfile->append = false;
		data->group[1].outfile->next = NULL;
		data->group[1].builtin = NULL;
		execution(data);
		free_groups(data);
		fake_parser(data, "22.3");
	}
	else if (ft_strncmp("22.3", test, 4) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(2, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("exit");
		data->group[0].full_cmd[1] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = NULL;
		data->group[0].builtin = NULL;
		execution(data);
		free_groups(data);
		fake_parser(data, "22.4");
	}
	else if (ft_strncmp("22.4", test, 4) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(2, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("pwd");
		data->group[0].full_cmd[1] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = malloc(sizeof(t_outfile));
		data->group[0].outfile->name = ft_strdup("minishell_tester/test22/outfile2");
		data->group[0].outfile->append = false;
		data->group[0].outfile->next = NULL;
		data->group[0].builtin = NULL;
		return (execution(data), free_data(data), exit(0));
	}
	else if (ft_strncmp("23", test, 2) == 0)
	{
		data->groupc = 2;
		data->group = ft_calloc(sizeof(t_group), 2);
		data->group[0].full_cmd = ft_calloc(3, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("echo");
		data->group[0].full_cmd[1] = ft_strdup("yo what is up\n yo yo yo");
		data->group[0].full_cmd[2] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = NULL;
		data->group[0].builtin = NULL;
		data->group[1].full_cmd = ft_calloc(3, sizeof(char *));
		data->group[1].full_cmd[0] = ft_strdup("grep");
		data->group[1].full_cmd[1] = ft_strdup("yo");
		data->group[1].full_cmd[2] = NULL;
		data->group[1].infile = NULL;
		data->group[1].outfile = malloc(sizeof(t_outfile));
		data->group[1].outfile->name = ft_strdup("minishell_tester/test23/outfile1");
		data->group[1].outfile->append = false;
		data->group[1].outfile->next = NULL;
		data->group[1].builtin = NULL;
	}
	else if (ft_strncmp("24", test, 2) == 0)
	{
		data->groupc = 4;
		data->group = ft_calloc(sizeof(t_group), 4);
		data->group[0].full_cmd = ft_calloc(3, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("echo");
		data->group[0].full_cmd[1] = ft_strdup("hola");
		data->group[0].full_cmd[2] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = NULL;
		data->group[0].builtin = NULL;
		data->group[1].full_cmd = ft_calloc(3, sizeof(char *));
		data->group[1].full_cmd[0] = ft_strdup("cat");
		data->group[1].full_cmd[1] = NULL;
		data->group[1].infile = NULL;
		data->group[1].outfile = NULL;
		data->group[1].builtin = NULL;
		data->group[2].full_cmd = ft_calloc(3, sizeof(char *));
		data->group[2].full_cmd[0] = ft_strdup("cat");
		data->group[2].full_cmd[1] = NULL;
		data->group[2].infile = NULL;
		data->group[2].outfile = NULL;
		data->group[2].builtin = NULL;
		data->group[3].full_cmd = ft_calloc(3, sizeof(char *));
		data->group[3].full_cmd = ft_calloc(3, sizeof(char *));
		data->group[3].full_cmd[0] = ft_strdup("grep");
		data->group[3].full_cmd[1] = ft_strdup("hola");
		data->group[3].full_cmd[2] = NULL;
		data->group[3].infile = NULL;
		data->group[3].outfile = malloc(sizeof(t_outfile));
		data->group[3].outfile->name = ft_strdup("minishell_tester/test24/outfile1");
		data->group[3].outfile->append = false;
		data->group[3].outfile->next = NULL;
		data->group[3].builtin = NULL;
	}
	else if (ft_strncmp("25", test, 4) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(3, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("cd");
		data->group[0].full_cmd[1] = ft_strdup("/Users/mialbert/Documents");
		data->group[0].full_cmd[2] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = NULL;
		data->group[0].builtin = NULL;
		execution(data);
		free_groups(data);
		fake_parser(data, "25.1");
	}
	else if (ft_strncmp("25.1", test, 4) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(3, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("/bin/pwd");
		data->group[0].full_cmd[1] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = ft_calloc(sizeof(t_outfile), 1);
		data->group[0].outfile->name = ft_strdup("minishell_tester/test25/outfile1");
		data->group[0].outfile->append = false;
		data->group[0].outfile->next = NULL;
		data->group[0].builtin = NULL;
		return (execution(data), exit(0));
	}
	else if (ft_strncmp("26", test, 4) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(3, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("bin/ls");
		data->group[0].full_cmd[1] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = NULL;
		data->group[0].builtin = NULL;
		execution(data);
		free_groups(data);
		fake_parser(data, "26.1");
	}
	else if (ft_strncmp("26.1", test, 4) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(3, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("echo");
		data->group[0].full_cmd[1] = ft_strdup("$?");
		data->group[0].full_cmd[2] = NULL;
		data->group[0].infile = NULL;
		data->group[0].outfile = ft_calloc(sizeof(t_outfile), 1);
		data->group[0].outfile->name = ft_strdup("minishell_tester/test26/outfile1");
		data->group[0].outfile->append = false;
		data->group[0].outfile->next = NULL;
		data->group[0].builtin = NULL;
		return (execution(data), exit(0));
	}
	else if (ft_strncmp("27", test, 2) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(3, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("grep");
		data->group[0].full_cmd[1] = ft_strdup("yo");
		data->group[0].full_cmd[2] = NULL;
		data->group[0].infile = malloc(sizeof(t_infile));
		data->group[0].infile->name = ft_strdup("minishell_tester/test26/infile1");
		data->group[0].infile->here_doc = true;
		data->group[0].infile->next = malloc(sizeof(t_infile));
		data->group[0].infile->next->name = ft_strdup("minishell_tester/test26/infile2");
		data->group[0].infile->next->here_doc = true;
		data->group[0].infile->next->next = NULL;
		data->group[0].outfile = malloc(sizeof(t_infile));
		data->group[0].outfile->name = ft_strdup("minishell_tester/test26/outfile1");
		data->group[0].outfile->append = false;
		data->group[0].outfile->next = malloc(sizeof(t_infile));
		data->group[0].outfile->next->name = ft_strdup("minishell_tester/test26/outfile2");
		data->group[0].outfile->next->append = false;
		data->group[0].outfile->next->next = NULL;
	}
	else if (ft_strncmp("28", test, 2) == 0)
	{
		data->groupc = 1;
		data->group = ft_calloc(sizeof(t_group), 1);
		data->group[0].full_cmd = ft_calloc(2, sizeof(char *));
		data->group[0].full_cmd[0] = ft_strdup("env");
		data->group[0].full_cmd[1] = NULL;
		data->group[0].infile = malloc(sizeof(t_infile));
		data->group[0].infile->name = ft_strdup("minishell_tester/test27/infile1");
		data->group[0].infile->here_doc = true;
		data->group[0].infile->next = malloc(sizeof(t_infile));
		data->group[0].infile->next->name = ft_strdup("minishell_tester/test27/infile2");
		data->group[0].infile->next->here_doc = true;
		data->group[0].infile->next->next = NULL;
		data->group[0].outfile = malloc(sizeof(t_infile));
		data->group[0].outfile->name = ft_strdup("minishell_tester/test27/outfile1");
		data->group[0].outfile->append = false;
		data->group[0].outfile->next = malloc(sizeof(t_infile));
		data->group[0].outfile->next->name = ft_strdup("minishell_tester/test27/outfile2");
		data->group[0].outfile->next->append = false;
		data->group[0].outfile->next->next = NULL;
	}
}

static void	init(t_data *data, char **envp)
{
	ft_printf_fd(STDERR_FILENO, "in init\n");
	ft_bzero(data, sizeof(data));
	data->paths = NULL;
	env_innit(data, envp);
	ft_printf_fd(STDERR_FILENO, "after env_innit\n");
	path_innit(data);
	ft_printf_fd(STDERR_FILENO, "after path_innit\n");
	init_pwd(data);
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

void	free_fds()
{
	int	i;

	i = 3;
	while (i <= 4096)
		close(i++);
}

int32_t	main(int32_t argc, char **argv, char **envp)
{
	// char	*str;
	t_data	data;

	(void)argc;
	(void)argv;
	(void)envp;
	init(&data, envp);
	if (argv[1])
	{
		ft_printf_fd(STDERR_FILENO, "after if argv[1]\n");
		fake_parser(&data, argv[1]);
		execution(&data);
	}
	// else
	// {
	// 	while (69)
	// 	{
	// 		// signal(SIGINT, ctrl_c);
	// 		// signal(SIGQUIT, ctrl_bslash);
	// 		signal(SIGQUIT, SIG_IGN);
	// 		str = readline("🦇Mishell: ");
	// 		if (str == NULL)
	// 			return (printf("exit\n"), 0);
	// 		if (ft_strncmp(str, "./minishell", 12))
	// 			execution(&data);
	// 		// str = ft_strdup("export hi | env");
	// 		// parser(&data, str);
	// 		add_history(str);
	// 		free(str);
	// 	}
	// }
	free_data(&data);
	return (0);
}
