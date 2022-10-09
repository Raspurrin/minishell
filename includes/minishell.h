/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 20:00:04 by mialbert          #+#    #+#             */
/*   Updated: 2022/10/08 20:15:31 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <stdint.h>
# include <dirent.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libs/libft/includes/libft.h"

typedef struct s_group	t_group;
typedef struct s_data	t_data;
typedef void			(t_func)(t_data *data, t_group *group);

typedef struct s_outfile
{
	char	*name;
	int32_t	fd;
	bool	append;
}	t_outfile;

typedef struct s_infile
{
	char	*name;
	int32_t	fd;
	bool	here_doc;
}	t_infile;

/**
 * This encompasses everything between/before/after pipelines. 
 * Information that purtains to one command. 
 * -> <infile1 <infile2 cmd >outfile1 >outfile2 <- | cmd2 >outfile3
 * We have an array of these structs in the data struct. To seperate
 * information for each "pipegroup".
 */
typedef struct s_group
{
	char		**full_cmd;
	t_infile	*infile;
	t_outfile	*outfile;
	size_t		infilec;
	size_t		outfilec;
	t_func		*builtin;
}	t_group;

typedef struct s_env
{
	char			*keyvalue;
	char			*key;
	char			*value;
	bool			printed;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	// DIR		*dirp;
	char	**paths;
	t_env	*envp_head;	
	t_group	*group;
	char	*pwd;
	size_t	groupc;
	size_t	envpc;
}	t_data;

// general 
void	init(t_data *data, char **envp);
void	display_error(t_data *data, char *error_msg, bool yeet);
void	free_at_exit(t_data *data);

// environment variable linked list handlers
void	print_env(t_data *data, t_group *group);
char	**env_2darr(t_data *data, t_env *lst);
void	print_group(void);

// execution
void	execution(t_data *data);
void	infiles(t_data *data, t_group *group);
void	outfiles(t_group *group, int32_t fd[2]);
char	*get_path(t_data *data);

// builtins:
void	exit_check(t_data *data, t_group *group);
void	cd(t_data *data, t_group *group);
void	echo(t_data *data, t_group *group);
void	exit_check(t_data *data, t_group *group);
void	export(t_data *data, t_group *group);
void	export_add(t_data *data, t_group *group);
void	pwd(t_data *data, t_group *group);
char	*init_pwd(t_data *data);
void	unset(t_data *data, t_group *group);

#endif