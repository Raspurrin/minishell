/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 20:00:04 by mialbert          #+#    #+#             */
/*   Updated: 2022/10/06 14:06:47 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <stdint.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libs/libft/includes/libft.h"

typedef struct s_outfile
{
	char	*name;
	bool	append;
}	t_outfile;

typedef struct s_infile
{
	char	*name;
	bool	here_doc;
}	t_infile;

typedef struct s_arg
{
	char		**full_cmd;
	t_infile	*infile;
	t_outfile;	outfile;
	char		**outcreate;
	bool		builtin;
}	t_arg;

typedef struct s_data
{
	char	**envp;	
	t_arg	*args;
	size_t	cmdc;
}	t_data;

typedef struct s_parsing
{
	
}	t_parsing;

void	execution(t_data *data);

#endif