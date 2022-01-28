#include "minishell.h"

void	parse()
{
	// execve();
}

int		main()
{
	char	*save;
    while ((save = readline("microshell > "))) 
	{
		printf("readlined: %s\n", save);
		add_history(save);
		parse();
	}
}