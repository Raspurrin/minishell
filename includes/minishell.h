/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 20:00:04 by mialbert          #+#    #+#             */
/*   Updated: 2022/10/10 19:28:52 by pmoghadd         ###   ########.fr       */
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
	struct s_outfile	*next;
}	t_outfile;

typedef struct s_infile
{
	char	*name;
	bool	here_doc;
	struct s_infile	*next;
}	t_infile;

typedef struct s_command
{
	char	*word;
	struct s_command	*next;
}t_command;

typedef struct s_group
{
	char		**full_cmd;
	t_command	*word;
	t_infile	*infile;
	t_outfile	*outfile;
	size_t		infilec;
	size_t		outfilec;
	int				read_in;
	int				read_out;
}	t_group;


typedef struct s_data
{
	char	**envp;	
	t_group	*args;
	size_t	cmdc;
}	t_data;

typedef struct t_parsing
{
	char	*infile;
	char	*outfile;
	char	*command;
	struct	t_parsing	*next;
}	t_parsing;

typedef struct token
{
	char			*command;
	char			**command_ops;
	t_infile		*infile;
	t_outfile		*outfile;
	size_t				counter_infile;
	size_t			counter_outfile;
	int				read_in;
	int				read_out;
	struct token	*next;
}t_token;

void	execution(t_data *data);
char	**minishell_split(char const *s, char c, char q);

int	skip_spaces(char *s);

/*		initialize		*/

void	lstaddback(t_infile **lst, t_infile *new);
void	lstaddback_out(t_outfile **lst, t_outfile *new);
void	initialize(t_group	**data);
void	words_init(t_group	**info, char *name);
void	out_file_init(t_group	**info, char *s, char *name);
void	in_file_init(t_group	**info, char *s, char *name);



/*		lexical_scan	*/
int		skip_quotes(char *s);
int		special_chars(t_group **info, char *s);
int		skip_chars(char *s);
int		quoted_word_extract(t_group **info, char *s);
int		normal_word_extract(t_group **info, char *s);




#endif