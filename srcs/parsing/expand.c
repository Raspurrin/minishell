/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 14:50:42 by pooneh            #+#    #+#             */
/*   Updated: 2022/11/03 20:29:50 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/minishell.h"

char *find_variable_part(char *string)
{
	int	i;

	i = 0;
	if (string[0] && (string[0] == '\'' || string[0] == '"'))
	{
		i = skip_quotes(string);
		return (ft_substr(string, 1, i - 2));
	}
	while (string[i] && ft_isalnum(string[i]))
		i++;
	return (ft_substr(string, 0, i));
}

char	*add_the_tail_of_string(char *value, char *dol_ptr, char *variable)
{
	int		i;
	int		j;
	char	*tail;
	int		end;

	i = 1;
	j = 0;
	tail = malloc (sizeof(char) * ft_strlen(dol_ptr));
	if (!tail)
		return (NULL);
	if (dol_ptr[i] && (dol_ptr[i] == '"' || dol_ptr[i] == '\''))
	{
		while (dol_ptr[i] && variable[i - 1] && (dol_ptr[i + 1] == variable[i - 1]))
			i++;
		i = i + 2;
		printf("1\n");
	}
	else
	{
		while (dol_ptr[i] && variable[i - 1] && dol_ptr[i] == variable[i - 1])
			i++;
		printf("2\n");
	}
	if (!ft_isalnum(dol_ptr[i]) && dol_ptr[i] != '"' && dol_ptr[i] != '\'')
	{
		tail[0] = dol_ptr[i];
		value = ft_strjoin(value, &tail[0]);
		printf("3\n");
	}
	else if (dol_ptr[i] && (dol_ptr[i] == '"' || dol_ptr[i] == '\''))
	{
		end  = skip_quotes(dol_ptr + i);
		tail = ft_substr(dol_ptr + i, 1, end - 2);
		value = ft_strjoin(value, tail);
		printf("4\n");
	}
	printf("tail|%s|\n", tail);
	// free (tail);
	return (value);
}

char	*expand(t_data *data, char *name)
{
	char	*variable;
	char	*dol_ptr;
	char	*value;
	t_env	*lst;

	lst = data->envp_head;
	dol_ptr = ft_strchr(name, '$');
	variable = dol_ptr + 1;
	variable = find_variable_part(variable);
	value = ft_substr(name, 0, ft_strlen(name) - ft_strlen(dol_ptr));
	printf("variable %s  value %s\n", variable, value);
	while (lst != NULL)
	{
		if (ft_strncmp(variable, lst->key, ft_strlen(variable)) == 0)
			value = ft_strjoin(value, lst->value);
		lst = lst->next;
	}
	value = add_the_tail_of_string(value, dol_ptr, variable);
	return (value);
}