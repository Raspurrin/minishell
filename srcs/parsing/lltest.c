#include "../includes/minishell.h"
#include <stdlib.h>

int	skip_spaces(char *s)
{
	int i;

	i = 0;
	while (s[i] && ( s[i] == ' ' || s[i] == '\t' || s[i] == '\n')) //add all the white spaces
		i++;
	return (i);
}

void	initialize(t_token	*data)
{
	data = (t_token *)malloc(sizeof(t_token));
	if (!data)
		return ; //error management?
	data->next = NULL;
}

int	find_next(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

void	add_infile(char *s, t_token *data, int k)
{
	int	space;
	int	l;

	space = skip_spaces(s);
	l = find_next(s + space, ' ');
	data->infile[k]= ft_substr(s, space, l);
    printf("LLtestL:%s\n",data->infile[k]);
    data = data->next;
}

void	make_token(char *s, t_token *data)
{
	int		i;
	char	c;
    int     counter;

	i = 0;
    counter = 0;
	while (s[i])
	{
		if (s[i] == '<')
		{
            add_infile(s + i + 1, data, counter);
            counter++;
        }
        i++;
	}
}


int main()
{
    char *s = "<   infile  <pooneh";
    t_token *data;

    initialize(data);
    make_token(s, data);
    printf("the ll input file:%s\n", data->infile[1]);

}