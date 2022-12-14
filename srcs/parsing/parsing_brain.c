/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_brain.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:07:48 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/24 17:39:51 by pmoghadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "../../includes/minishell.h"

void	make_token(char *s, t_group **info, t_env *envp)
{
	int		i;

	i = 0;
	initialize(info);
	while (i < (int)ft_strlen(s))
	{
		if (s[i] && (s[i] == '>' || s[i] == '<'))
		{
			(*info)->read_in = special_chars(info, s + i, envp);
			i = i + (*info)->read_in + 1;
		}
		else if (s[i] && (s[i] == '"' || s[i] == '\''))
		{
			(*info)->read_in = quoted_word_extract(info, s + i, envp);
			i = i + (*info)->read_in;
		}
		else if (s[i] && s[i] != ' ')
		{
			(*info)->read_in = normal_word_extract(info, s + i, envp);
			i = i + (*info)->read_in;
		}
		i++;
	}
	if ((*info)->commandc == 0)
		(*info)->full_cmd = NULL;
}

void	parser(char *str, t_env *envp, t_data *data)
{
	int		i;
	char	**pipe_wise_splitted;
	t_group	*tmp;

	i = 0;
	if (!check_input_before_parsing(str))
	{
		pipe_wise_splitted = ft_split_shell(str, '|');
		first_initialization(pipe_wise_splitted, data);
		while (pipe_wise_splitted[i])
		{
			tmp = &(data->group[i]);
			make_token(pipe_wise_splitted[i], &tmp, envp);
			free(pipe_wise_splitted[i]);
			i++;
		}
		free(pipe_wise_splitted);
	}
	data->groupc = i;
}
