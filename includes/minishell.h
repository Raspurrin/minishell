/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:45:27 by pmoghadd          #+#    #+#             */
/*   Updated: 2022/10/31 22:39:45 by mialbert         ###   ########.fr       */
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
# include <sys/signal.h>
# include <sys/wait.h>
# include <signal.h>
// # include <readline/readline.h>
// # include <readline/history.h>
# include </Users/mialbert/goinfre/.brew/opt/readline/include/readline/readline.h>
# include </Users/mialbert/goinfre/.brew/opt/readline/include/readline/history.h>
# include "../libs/libft/includes/libft.h"

# define READ 0
# define WRITE 1
# define FOLDER1 "minishell_tester/test1/"
# define FOLDER2 "minishell_tester/test2/"
# define FOLDER3 "minishell_tester/test3/"
# define FOLDER4 "minishell_tester/test4/"
# define FOLDER5 "minishell_tester/test5/"

typedef struct s_group	t_group;
typedef struct s_data	t_data;
typedef void			(*t_builtin)(t_data *, t_group *);

typedef struct s_outfile
{
	char				*name;
	bool				append;
	struct s_outfile	*next;
}	t_outfile;

typedef struct s_infile
{
	char			*name;
	bool			here_doc;
	struct s_infile	*next;
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
	t_builtin	builtin;
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
	int32_t	status;
	char	**paths;
	t_env	*envp_head;	
	t_group	*group;
	char	*pwd;
	size_t	groupc;
	size_t	envpc;
	int32_t	tmp_fd;
}	t_data;

typedef struct t_parsing
{
	char				*infile;
	char				*outfile;
	char				*command;
	struct t_parsing	*next;
}	t_parsing;

typedef struct token
{
	char			*command;
	char			**command_ops;
	t_infile		*infile;
	t_outfile		*outfile;
	size_t			counter_infile;
	size_t			counter_outfile;
	int				read_in;
	int				read_out;
	struct token	*next;
}	t_token;

/*		initialize		*/
char	**minishell_split(char const *s, char c, char q);
void	lstaddback(t_infile **lst, t_infile *new);
void	lstaddback_out(t_outfile **lst, t_outfile *new);
void	initialize(t_group	**data);
void	words_init(t_group	**info, char *name);
void	out_file_init(t_group	**info, char *s, char *name);
void	in_file_init(t_group	**info, char *s, char *name);

/*		lexical_scan	*/
int		skip_quotes(char *s);
int		skip_spaces(char *s);
int		special_chars(t_group **info, char *s);
int		skip_chars(char *s);
int		quoted_word_extract(t_group **info, char *s);
int		normal_word_extract(t_group **info, char *s);

/* general */
void	display_error(t_data *data, char *error_msg, bool yeet);
void	free_at_exit(t_data *data);
void	free_data(t_data *data);

/* environment variable linked list handlers */
void	print_env(t_data *data, t_group *group);
char	**env_2darr(t_data *data, t_env *lst);
void	print_group(void);
t_env	*find_node(t_env *lst, char *key);

/* execution */
void	env_innit(t_data *data, char **envp);
void	execution(t_data *data);
bool	infiles(t_data *data, t_group *group);
bool	outfiles(t_data *data, t_group *group);
char	*get_path(t_data *data);
char	*find_path(t_data *data, size_t	group_i);
void	path_innit(t_data *data);

/* builtins: */
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
