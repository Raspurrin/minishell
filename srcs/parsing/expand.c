/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 14:50:42 by pooneh            #+#    #+#             */
/*   Updated: 2022/11/19 15:20:07 by pmoghadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/minishell.h"

char *find_variable_part(char *string)
{
	int	i;

	i = 0;
	if(string[i] && first_char_check(string[i]))
	{
		if (string[i] && (string[i] == '\''|| string[i] == '"'))
			i += skip_quotes(string + i);
		while (string[i] && ft_isalnum_ms(string[i]))
			i++;
		if (i == 0) //for now to avoid seg fault when non alphabetical parameters are there. 
			return("0");
		return (ft_substr(string, 0, i));
	}
	else
		return (ft_substr(string, 0, 1));
}

int	replace_variable_value(char **name, int index, char	*variable, t_env *envp)
{
	int	i;
	int	l;
	char	*tmp_tail;
	char	*tmp_head;

	i = 0;
	l = 0;
	tmp_tail = *name + index + ft_strlen(variable);
	// if (index > 1)
		tmp_head = ft_substr(*name, 0, index - 1);
	// else
	// 	tmp_head = "";
	while (envp)
	{
		if (!ft_strncmp(variable, envp->key, ft_strlen(variable)))
		{
			tmp_head = ft_strjoin_minishell(tmp_head, envp->value);
			l = ft_strlen(envp->value);
		}
		else if (!ft_strncmp(variable, "?", 1))
			tmp_head = ft_strjoin_minishell(tmp_head, envp->key);
		envp = envp->next;
	}
	if (l == 0 && (variable[0] == '"' || variable[0] == '\''))
		tmp_head = ft_strjoin_minishell(tmp_head, variable);
	tmp_head = ft_strjoin_minishell(tmp_head, tmp_tail); //changed for leaks
	*name = tmp_head;
	return (l + index);
}

char	*expand(char *name, t_env *envp)
{
	char	*variable;
	int		i;

	i = 0;
	while (name[i])
	{
		if (name[i] == '\'' && name[skip_quotes(name + i) - 1] == '\'')
			i += skip_quotes(name + i);
		if (name[i] == '$')
		{
			variable = find_variable_part(name + i + 1);
			i = replace_variable_value(&name, i + 1, variable, envp) - 1;
			i--;
		}
		i++;
	}
	return (name);
}
