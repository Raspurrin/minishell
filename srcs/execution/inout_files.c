/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inout_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 03:43:43 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/12 01:19:43 by mialbert         ###   ########.fr       */
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
	fd = open(lst->name, O_RDWR | O_CREAT | O_TRUNC, 0666);
	printf("fd in heredoc: %d\n", fd);
	ft_printf_fd(STDERR_FILENO, "In heredoc\n");
	if (fd == -1)
		display_error(data, "Heredoc inout_files, Open infile failed", true);
	while (ft_strncmp(line, lst->name, ft_strlen(lst->name) + 1) != 10)
	{
		free(line);
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
			return (unlink(lst->name), 0); // instead of handling signals lol
		write(fd, line, ft_strlen(line));
	}
	free(line);
	close(fd);
	fd = open(lst->name, O_RDONLY, 0666);
	return (fd);
}

bool	infiles(t_data *data, t_group *group)
{
	int32_t		fd;
	t_infile	*lst;

	// fd = -1;
	lst = group->infile;
	(void)data;
	while (lst != NULL)
	{
		if (lst->here_doc == true)
		{
			fd = here_doc(data, lst);
			if (!fd)
				break; // weird behaviour 
		}
		else
		{
			fd = open(lst->name, O_RDONLY, 0666);
			if (fd == -1)
			{
				free_fds();
				display_error(data, "Opening infile failed", true);
			}
		}
		if (lst->next == NULL)
		{
			printf("fd in infiles: %d\n", fd);
			printf("name: %s\n", lst->name);
			if (dup2(fd, STDIN_FILENO) == -1)
				printf("yooo dup2 failed\n");
			if (fd >= 0)
				close(fd);
			return (true);
		}
		if (fd >= 0)
			close(fd);
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
	ft_printf_fd(STDERR_FILENO, "%p\n", group->outfile);
	while (lst != NULL)
	{
		ft_printf_fd(STDERR_FILENO, "outfile: %s\n", lst->name);
		if (lst->append == !false)
		{
			ft_printf_fd(STDERR_FILENO, "is appended\n");
			flag = (O_RDWR | O_CREAT | O_APPEND);
		}
		else
		{
			ft_printf_fd(STDERR_FILENO, "is not appended\n");
			flag = (O_RDWR | O_CREAT | O_TRUNC);
		}
		ft_printf_fd(STDERR_FILENO, "opened: %s\nappend: %d\n", lst->name, lst->append);
		fd = open(lst->name, flag, 0666);
		if (fd == -1)
		{
			free_fds();
			display_error(data, "Opening outfile failed", true);
		}
		if (lst->next == NULL)
		{
			ft_printf_fd(STDERR_FILENO, "Dupping %s to STDOUT\n", lst->name);
			return (dup2(fd, STDOUT_FILENO), close(fd), true);
		}
		close(fd);
		lst = lst->next;
	}
	return (false);
}
