/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:07:48 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/15 12:55:21 by pmoghadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "../../includes/minishell.h"

// void executing(t_group *info) //just for test purposes
// {
// 	int	y;
// 	// t_outfile	*head = info->outfile;

// 	y = 0;
// 	while (info->full_cmd[y])
// 	{
// 		printf("i   %d    word|%s|\n", y, info->full_cmd[y]);
// 		y++;
// 	}
// 	// while (info->outfile != NULL)
// 	// {
// 	// 	printf("info->outfiles|%s|\n", info->outfile->name);
// 	// 	info->outfile = info->outfile->next;
// 	// }
// 	// info->outfile = head;
// 	while (info->infile != NULL)
// 	{
// 		printf("info->infiles|%s| %d\n", info->infile->name, info->infile->here_doc);
// 		info->infile = info->infile->next;
// 	}
// }

void	make_token(char *s, t_group *info, int index, char **envp, t_data *data)
{
	int		i;

	i = 0;
	info = (t_group *)malloc(sizeof(t_group));
	if (!info)
		return ;
	initialize(&info, index, envp);
	while (s[i])
	{
		if (s[i] && (s[i] == '>' || s[i] == '<'))
		{
			info->read_in = special_chars(&info, s + i);
			i = i + info->read_in + 1;
		}
		else if (s[i] && (s[i] == '"' || s[i] == '\''))
		{
			info->read_in = quoted_word_extract(&info, s + i);
			i = i + info->read_in;
		}
		else if (s[i] && s[i] != ' ')
		{
			info->read_in = normal_word_extract(&info, s + i);
			i = i + info->read_in;
		}
		i++;
	}
	info->full_cmd[info->commandc] = NULL;
	(void)data;
	//data->args = info;
	//executing(info); //parsed data is passed to execution.
}

void	parser(char *str, char **envp, t_data *data)
{
	int		i;
	char	**pipe_wise_splitted;
	t_group	*array_of_struct;

	i = 0;
	if (!check_input_before_handling(str))
	{
		pipe_wise_splitted = ft_split_shell(str, '|');
		first_initialization(pipe_wise_splitted, &array_of_struct);
		while (pipe_wise_splitted[i])
		{
			make_token(pipe_wise_splitted[i], (&array_of_struct[i]), i, envp, data);
			i++;
		}
	}
	else
}

// int32_t	main(int argc, char **argv, char **envp)
// {
// 	char	*str;
// 	t_data	*data;
// 	int		i;

// 	(void)argc;
// 	(void)argv;
// 	data = NULL;
// 	i = 0;
// 	while (1000)
// 	{
// 		str = readline(" Minihell: ");
// 		if (str == NULL)
// 			break ;
// 		add_history(str);
// 		parser(str, envp, data);
// 		// execution(data);

		
// 		free(str);
// 	}
// 	return (0);
// }
