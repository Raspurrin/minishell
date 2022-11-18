#include<stdio.h>
int	skip_quotes(char *s)
{
	char	quote_type;
	int		i;

	i = 1;
	quote_type = s[0];
	while (s[i] && s[i] != quote_type)
		i++;
	return (i + 1);
}
int main()
{
    char *s= "'1235'";
    printf("%d", skip_quotes(s));
}