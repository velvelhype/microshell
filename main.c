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

typedef	struct	s_list{
	char	**tokens;
	struct s_list	*next;
} t_list;

// void	launch(t_list *lists)
// {
// 	int fork_ret = fork();
// 	if (fork_ret == 0)
// 	{
// 		int child_status;
// 		int	fildes[2];
// 		pipe(fildes);
// 		fork_ret = fork();
// 		if (fork_ret == 0)
// 		{
// 			dup2(fildes[1], 1);
// 			close(fildes[1]);
// 			execvp(lists[0].tokens[0], lists[0].tokens);
// 		}
// 		else
// 		{
// 			dup2(fildes[0], 0);
// 			close(fildes[1]);
// 			execvp(lists[1].tokens[0], lists[1].tokens);
// 		}
// 	}
// 	wait (NULL);
// }

// void	launch(t_list *list)
// {
// 	int	fds[2];

// 	pipe(fds);
// 	launch_rec(list);
// }

void	launch_rec(t_list *list, int *fds)
{
	if ((list->next)->tokens)
	{
		//set fds
		int fork_ret = fork();
		if (!fork_ret)
			execvp(list->tokens[0], list->tokens);
		else
		{	
			wait(NULL);
			launch_rec(list->next, fds);
		}
	}
	else
	{
		//set fds
		int fork_ret = fork();
		if (!fork_ret)
			execvp(list->tokens[0], list->tokens);
		else
		{
			wait(NULL);
			printf("end!\n");
		}
	}
}

void	parse(char *save)
{
	char	**splitted = ft_split(save, '|');
	char	**split_a = ft_split(splitted[0], ' ');
	char	**split_b  = ft_split(splitted[1], ' ');
	char	**split_c  = ft_split(splitted[2], ' ');

	// print_all(splitted);
	// print_all(split_a);
	// print_all(split_b);
	t_list lists[4];
	lists[0].tokens = split_a;
	lists[0].next = &lists[1];
	lists[1].tokens = split_b;
	lists[1].next = &lists[2];
	lists[2].tokens = split_c;
	lists[2].next = &lists[3];
	lists[3].tokens = NULL;

	// launch(split_a, split_b);
	// launch(lists);
	int	fds[2];
	launch_rec(&lists[0], fds);
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
		free(save);
	}
}