#include "minishell.h"

int main()
{
	int fds[2];
	pipe(fds);
	int child = fork();

	if(child == 0)
	{
		dup2(fds[1], 1);
		close(fds[1]);
		printf("message\n");
	}
	else
	{
		char save[10];
		read(fds[0], save, 5);
		printf("save %s\n", save);
	}
}