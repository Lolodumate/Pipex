#include "pipex.h"

void	pipex(char **argv, int *end, t_pipex *p, pid_t pid)
{
	if (pid == -1)
	{
		clean(p->paths);
		free(p);
		perror("Error fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		child_process(argv, argv[2], end, p);
	else
		parent_process(argv, argv[3], end, p);
}
