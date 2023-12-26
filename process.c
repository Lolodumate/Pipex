#include "pipex.h"

int	create_process(pid_t pid)
{
	pid = fork(); // Creation du processus fils
	if (pid == -1) // Erreur
		return (1);
	if (pid == 0)
		printf("Processus fils cree. PID = %d\n", pid);
	else if (pid > 0)
		printf("Processus pere cree. PID = %d\n", pid);
	return (0);
}

int	get_process(pid_t pid) // pid == fork();
{
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		printf("This is the child process (pid : %d)\n", getpid());
	else
		printf("This is the parent process (pid : %d)\n", getpid());
	return (0);
}
/* For child process :
 * infile has to be the stdin (as input)
 * end[1] has to be the stdout (we write to end[1] the output of cmd1)
 */
void	child_process(int f1, int cmd1)
{
	int		end[2] = {0};

	// add protection if dup2() < 0
	// dup2() close stdin, f1 becomes the new stdin
	dup2(f1, STDIN_FILENO); // we want f1 to execve() input
	dup2(end[1], STDOUT_FILENO); // we want end[1] to be execve() stdout
	close(end[0]); // Always close the end of the pipe you don't use !
	close(f1);
	printf("%d", cmd1);
	// execve function for each possible path
	exit(EXIT_FAILURE);
}

/* For parent process :
 * end[0] has to be the stdin (end[0] reads from end[1] the output of cmd1)
 * outfile has to be the stdout(we write to it the output of cmd2)
 */
void	parent_process(int f2, int cmd2)
{
	int		status;
	int		end[2] = {0};
//	int		f1;

	status = 0;
	waitpid(-1, &status, 0); // To wait for the child to finish his process.
	
	f2 = open("example.txt", O_WRONLY | O_CREAT, 0644);
	if (f2 == -1)
		exit(EXIT_FAILURE);
	dup2(f2, STDOUT_FILENO); // f2 is the stdout.
	dup2(end[0], STDIN_FILENO); // end[0] is the stdin.
	close(end[1]);
	close(f2);
	printf("%d", cmd2);
	// execve function for each possible path
	exit(EXIT_FAILURE);
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
