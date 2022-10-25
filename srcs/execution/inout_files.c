/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inout_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 03:43:43 by mialbert          #+#    #+#             */
/*   Updated: 2022/10/24 22:28:43 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * A heredoc is a file literal. It is a multi-line string taken from STDIN
 * ended by a delimiter. It is then treated as an input file.
 * I create a temporary file where I store everything until the delimiter
 * is used and then delete it 
 */
static int32_t	here_doc(t_data *data, t_infile *lst)
{
	int32_t		fd;
	char		*line;

	line = ft_calloc(2, 1);
	printf("hi\n");
	fd = open(lst->name, O_RDWR | O_CREAT, 0666);
	ft_printf_fd(STDERR_FILENO, "In heredoc\n");
	if (fd == -1)
		display_error(data, "Heredoc inout_files, Open infile failed", true);
	while (ft_strncmp(line, lst->name, ft_strlen(lst->name) + 1) != 10)
	{
		free(line);
		line = get_next_line(STDIN_FILENO);
		printf("%s\n", line);
		write (fd, line, ft_strlen(line));
	}
	free(line);
	return (fd);
}

/**
 * @brief I have a boolean to check whether or not the file is a heredoc 
 * and treat it accordingly. Otherwise, I keep opening files and checking 
 * if it exists or not, in which case I throw an error and then I only 
 * dup the last inputfile/heredoc, as that is the only input considered
 * for the command.
 * @param group contains all the infiles, outfiles and commans of the 
 * current pipegroup.
 */
bool	infiles(t_data *data, t_group *group)
{
	int32_t		fd;
	t_infile	*lst;

	fd = 0;
	lst = group->infile;
	while (lst != NULL)
	{
		printf("=========in infiles=======\n");
		if (lst->here_doc == true)
			fd = here_doc(data, lst);
		else
		{
			fd = open(lst->name, O_RDONLY, 0666);
			if (fd == -1)
				display_error(data, "Opening infile failed", true);
			// close (fd);
		}
		if (lst->next == NULL)
		{
			// char	buf[1000];
			// ft_bzero(buf, 1000);
			// read(fd, buf, 1000);
			// ft_printf_fd(STDERR_FILENO, "name file: %s\n", lst->name);
			// ft_printf_fd(STDERR_FILENO, "reading file: %s\n", buf);
			// ft_printf_fd(STDERR_FILENO, "dupping infile to STDIN\n");
			// ft_printf_fd(STDERR_FILENO, "This is fd: %d\n", fd);
			// ft_printf_fd(STDERR_FILENO, "STDIN: %d\n", STDIN_FILENO);
			// ft_printf_fd(STDERR_FILENO, "This is dup return: %d\n", \
			// 								(dup2(fd, STDIN_FILENO)));
			// int fd2 = open("file1", O_RDONLY, 0666);
			dup2(fd, STDIN_FILENO);
			perror("perror: \n");
			// close(fd);
			return (true);
		}
		lst = lst->next;
	}
	return (false);
}

/**
 * @brief I check whether or not the outfile should use append mode.
 * And I always create the file, but I only consider the output of the 
 * last output file. Dup duplicates it to STDOUT: 
 * 0 - STDIN		->	0 - STDIN
 * 1 - STDOUT 			1 - fd		<- this temporarily closes STDOUT.
 * 2 - STDERR			2 - STDERR
 * 3 - fd 
 * @param group 
 */
bool	outfiles(t_data *data, t_group *group)
{
	int32_t		fd;
	int16_t		flag;
	t_outfile	*lst;

	lst = group->outfile;
	ft_printf_fd(STDERR_FILENO, "==========outfiles=========\n");
	while (lst != NULL)
	{
		if (lst->append == true)
			flag = (O_RDWR | O_CREAT | O_APPEND);
		else
			flag = (O_RDWR | O_CREAT | O_TRUNC);
		fd = open(lst->name, flag, 0666);
		if (fd == -1)
			display_error(data, "Opening outfile failed", true);
		if (lst->next == NULL)
		{
			printf("[OK] STDOUT can still be used\n");
			ft_printf_fd(STDERR_FILENO, "Dupping %s to STDOUT\n", lst->name);
			return (dup2(fd, STDOUT_FILENO), true);
		}
		close(fd);
		lst = lst->next;
	}
	return (false);
}
