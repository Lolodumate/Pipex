#include "pipex.h"

void	pipex(char **argv, int *end, t_pipex *p, pid_t pid)
{
	if (pid == -1)
	{
		free(p);
		perror("Error fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		close(end[0]);
		child_process(argv, argv[2], end, p);
		close(end[0]);
		close(end[1]);
		exit(EXIT_SUCCESS);
	}
	if (pid > 0)
	{
		close(end[1]);
//		wait(NULL);
		parent_process(argv, argv[3], end, p);
		close(end[0]);
		close(end[1]);
		exit(EXIT_SUCCESS);
	}

}
