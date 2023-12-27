#include "pipex.h"

void	pipex(char **argv, t_pipex *p)
{
	int		fd[2];
	pid_t	pid;

	pid = fork();
	ft_pipe(fd, pid, p, argv);
}
