#include "../includes/minishell.h"

int32_t	main(void)
{
	char *str;

	str = readline("test");
	printf("str: %s\n", str);
	return (0);
}
