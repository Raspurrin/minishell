/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 18:01:38 by pmoghadd          #+#    #+#             */
/*   Updated: 2022/11/24 11:55:43 by pmoghadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief the number of groups (dependant on the number of pipes)
 * is used here to make enough groups in for a group pointer in the data struct 
 * type.
 * 
 * @param pipe_wise_splitted_array 
 * @param data 
 */
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

/**
 * @brief initialized the linked lists of in and outfile and commands char ** space
 * is made
 * 
 * @param info 
 */
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

/**
 * @brief initialized the input linked list. creates a node of t_infile types and saves in
 * it wether it is a heredoc or input file. 
 * if a variable, it is expanded. if containing quotes, they are passed to the quote removal
 * func. 
 * @param info 
 * @param s 
 * @param name 
 * @param envp 
 */

void	in_file_init(t_group	**info, char *s, char *name, t_env *envp)
{
	t_infile	*new;

	new = malloc(sizeof(t_infile));
	if (!new)
		return ;
	if (ft_strchr(name, '$') && s[1] != '<')
		name = expand(name, envp);
	name = rm_quotes_all(name);
	new->name = name;
	if (s[1] == '<')
		new->here_doc = 1;
	else
		new->here_doc = 0;
	new->next = NULL;
	lstaddback(&(*info)->infile, new);
}

/**
 * @brief saves the output files names in the t_outfile linked list.
 * tells if it is normal or append. if a variable, it is expanded. 
 * if containing quotes, they are passed to the quote removal
 * func. 
 * 
 * @param info 
 * @param s 
 * @param name 
 * @param envp 
 */

void	out_file_init(t_group	**info, char *s, char *name, t_env *envp)
{
	t_outfile	*new;

	new = malloc(sizeof(t_outfile));
	if (!new)
		return ;
	if (ft_strchr(name, '$'))
		name = expand(name, envp);
	name = rm_quotes_all(name);
	new->name = name;
	if (s[1] == '<')
		new->append = 1;
	else
		new->append = 0;
	new->next = NULL;
	lstaddback_out(&(*info)->outfile, new);
}

/**
 * @brief words mean commands. every thing other than in/out files comes here and
 * is saved in a char ** 
 * if a variable, it is expanded. if containing quotes, they are passed to the quote removal
 * func. 
 * @param info 
 * @param name 
 * @param envp 
 */

void	words_init(t_group	**info, char *name, t_env *envp)
{
	char		**command_array;

	if (ft_strchr(name, '$'))
		name = expand(name, envp);
	name = rm_quotes_all(name);
	(*info)->commandc = (*info)->commandc + 1;
	command_array = (char **)realloc((*info)->full_cmd,
			sizeof(char *) * ((*info)->commandc + 1));
	// free((*info)->full_cmd);
	command_array[((*info)->commandc) - 1] = name;
	command_array[((*info)->commandc)] = NULL;
	(*info)->full_cmd = command_array;
}
