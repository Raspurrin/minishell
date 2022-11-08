/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 18:01:38 by pmoghadd          #+#    #+#             */
/*   Updated: 2022/11/07 14:42:56 by mialbert         ###   ########.fr       */
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

void	first_initialization(char **pipe_wise_splitted_array, t_group	**data)
{
	int	i;

	i = 0;
	while (pipe_wise_splitted_array[i])
		i++;
	data = (t_group **)malloc(sizeof(t_group *) * (i + 1));
	if (!data)
		return ;
}

void	initialize(t_group	**data, int index)
{
	(void)index;
	(*data)->infile = ft_calloc(sizeof(t_infile), 1);
	(*data)->outfile = ft_calloc(sizeof(t_outfile), 1);
	(*data)->outfile->next = NULL;
	(*data)->infile->next = NULL;
	(*data)->infile->here_doc = false;
	(*data)->outfile->append = false;
	(*data)->read_in = 0;
	(*data)->read_out = 0;
	(*data)->full_cmd = ft_calloc(3, sizeof(char *));
	(*data)->commandc = 0;
	(*data)->builtin = NULL;
	// printf("envp check%s\n", (*data)->envp[1]);
}

void	in_file_init(t_data *data, t_group	**info, char *s, char *name)
{
	t_infile	*new;

	new = malloc(sizeof(t_infile));
	if (!new)
		return ;
	new->name = name;
	if (ft_strchr(name, '$'))
		name = expand(data, name);
	printf("substr in|%s|\n", name);
	// free(name);
	if (s[1] == '<')
		new->here_doc = 1;
	else
		new->here_doc = 0;
	new->next = NULL;
	lstaddback(&(*info)->infile, new);
	// printf("ll test %s", (*info)->infile->name);
}

void	out_file_init(t_data *data, t_group	**info, char *s, char *name)
{
	t_outfile	*new;

	new = malloc(sizeof(t_outfile));
	if (!new)
		return ;
	if (ft_strchr(name, '$'))
		name = expand(data, name);
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

void	words_init(t_data *data, t_group	**info, char *name)
{
	char		**command_array;

	printf("%d\n",   (*info)->commandc + 2);
	if (ft_strchr(name, '$'))
		name = expand(data, name);
	(*info)->commandc = (*info)->commandc + 1;
	command_array = (char **)ft_realloc((*info)->full_cmd,
			sizeof(char *) * ((*info)->commandc) + 2);
	command_array[(*info)->commandc - 1] = name; // so command_array is initialized but not original info .-.
	(*info)->full_cmd
	[(*info)->commandc - 1] = command_array[(*info)->commandc - 1];
	(*info)->full_cmd[(*info)->commandc] = NULL;
}
