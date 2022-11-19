/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 18:01:38 by pmoghadd          #+#    #+#             */
/*   Updated: 2022/11/19 14:26:56 by pmoghadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_strlen_array(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	first_initialization(char **pipe_wise_splitted_array, t_data *data)
{
	int	i;

	i = 0;
	while (pipe_wise_splitted_array[i])
		i++;		
	data->group = (t_group *)malloc(sizeof(t_group) * (i + 1));
	if (!data)
		return ;
}

void	initialize(t_group	**info)
{
	(*info)->infile = NULL;
	(*info)->outfile = NULL;
	(*info)->read_in = 0;
	(*info)->read_out = 0;
	(*info)->full_cmd = (char **)ft_calloc(sizeof(char *), 1);
	if (!(*info)->full_cmd)
		return ;
	(*info)->commandc = 0;
}

void	in_file_init(t_group	**info, char *s, char *name, t_env *envp)
{
	t_infile	*new;

	new = malloc(sizeof(t_infile));
	if (!new)
		return ;
	if (ft_strchr(name, '$'))
		name = expand(name, envp);
	if(name[0] == '\"' || name[0] == '\'')
		name = remove_quotes(name);
	new->name = name;
	// printf("substr in|%s|\n", name);
	// free(name);
	if (s[1] == '<')
		new->here_doc = 1;
	else
		new->here_doc = 0;
	new->next = NULL;
	lstaddback(&(*info)->infile, new);
	// printf("ll test %s\n", (*info)->infile->next->name);
}

void	out_file_init(t_group	**info, char *s, char *name, t_env *envp)
{
	t_outfile	*new;

	new = malloc(sizeof(t_outfile));
	if (!new)
		return ;
	if (ft_strchr(name, '$'))
		name = expand(name, envp);
	if(name[0] == '\"' || name[0] == '\'')
		name = remove_quotes(name);
	new->name = name;
	// printf("substr out|%s|\n", new->name);
	if (s[1] == '<')
		new->append = 1;
	else
		new->append = 0;
	new->next = NULL;
	lstaddback_out(&(*info)->outfile, new);
	// free(name);
}

void	words_init(t_group	**info, char *name, t_env *envp)
{
	char		**command_array;

	if (ft_strchr(name, '$'))
		name = expand(name, envp);
	if(name[0] == '\"' || name[0] == '\'')
		name = remove_quotes(name);
	(*info)->commandc = (*info)->commandc + 1;
	command_array = (char **)ft_realloc((*info)->full_cmd,
			sizeof(char *) * ((*info)->commandc) + 2);
	free((*info)->full_cmd);
	command_array[((*info)->commandc) - 1] = name;
	command_array[((*info)->commandc)] = NULL;
	(*info)->full_cmd = command_array;
}
