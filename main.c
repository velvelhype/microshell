#include "minishell.h"
#include <stdio.h>

void	print_all(char **save)
{
	printf("has-----\n");
	while (*save)
	{
		printf("%s\n", *save);
		save++;
	}
	printf("--------\n");
}

void	parse(char *save)
{
	char	**splitted = ft_split(save, '|');
	char **split_a = ft_split(splitted[0], ' ');
	char **split_b  = ft_split(splitted[1], ' ');
	// print_all(splitted);
	// print_all(split_a);
	// print_all(split_b);
	int fork_ret = fork();
	if (fork_ret == 0)
	{
		int child_status;
		int	fildes[2];
		pipe(fildes);
		fork_ret = fork();
		if (fork_ret == 0)
		{
			dup2(fildes[1], 1);
			// close(fildes[0]);
			execvp(split_a[0], split_a);
		}
		else
		{
			dup2(fildes[0], 0);
			// close(fildes[0]);
			close(fildes[1]);
			execvp(split_b[0], split_b);
		}
	}
}

int		main(int argc, char **argv, char **envp)
{
	char	*save;
	int		fork_ret;
	int		child_status;

    while ((save = readline("microshell > "))) 
	{
		add_history(save);
		parse(save);
	}
}