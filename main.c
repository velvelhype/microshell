#include <unistd.h>

int main(int ac, char **argv, char **envp)
{
	execve("bin/bash", argv, envp);
}