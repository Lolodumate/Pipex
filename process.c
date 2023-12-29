#include "pipex.h"

/* For child process :
 * infile has to be the stdin (as input)
 * end[1] has to be the stdout (we write to end[1] the output of cmd1)
 */

void	child_process(char **argv, char *cmd, int *end, t_pipex *p)
{
	int		fd;

	if (!argv || !argv[1])
	{
		exit(EXIT_FAILURE);
	}
	fd = open(argv[1], O_RDONLY, 0644); // 0777 au lieu de 0644
        if (fd == -1)
		exit(EXIT_FAILURE);
	dup2(fd, STDIN_FILENO); // we want fd to execve() input
	close(fd);
	close(end[0]); // Always close the end of the pipe you don't use !
	dup2(end[1], STDOUT_FILENO); // we want end[1] to be execve() stdout
	exec_command(p->paths, cmd);
}

/* For parent process :
 * end[0] has to be the stdin (end[0] reads from end[1] the output of cmd1)
 * outfile has to be the stdout(we write to it the output of cmd2)
 */
void	parent_process(char **argv, char *cmd, int *end, t_pipex *p)
{
	int		status;
	int		fd;

	waitpid(-1, &status, 0); // To wait for the child to finish his process.
	close(end[1]);
	if (!argv || !argv[4])
		exit(EXIT_FAILURE);
	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit(EXIT_FAILURE);
	dup2(fd, STDOUT_FILENO); // f2 is the stdout.
	dup2(end[0], STDIN_FILENO); // end[0] is the stdin.
	close(end[0]);
	close(fd);
	exec_command(p->paths, cmd);
}

int	wait_process(pid_t pid)
{
	if (pid == -1)
	{
		perror("Error fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		printf("I am the child process.\n");
		sleep(2);
		exit(EXIT_SUCCESS);
	}
	else
	{
		printf("I am the parent process.\n");
		wait(NULL);
		printf("Child process terminated after a 2s delay.\n");
	}
	return (EXIT_SUCCESS);
}
