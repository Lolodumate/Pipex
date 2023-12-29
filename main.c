#include "pipex.h"

/*  Source : https://csnotes.medium.com/pipex-tutorial-42-project-4469f5dd5901
 *
 *  1. Read from infile
 *  2. Execute cmd1 with infile as input
 *  3. Send the ouput to cmd2
 *  4. Write the outfile
 *
 *  end[1] is child process : child (infile is stdin) executes cmd1 and writes (end[1] is stdout).
 *  end[0] is parent process : parent (end[0] is stdin) reads and executes cmd2 (outfile is stdout).
 * 
 *  ./pipex infile cmd1 cmd2 outfile
 *  Pipe creates files descriptors.
 *  -------------------------------------------------------------------------------------------------
 *  dup2() can swap our fds to stdin/stdout.
 *  dup2() close fd2 and duplicate the value of fd2 to fd1 or it will redirect fd1 to fd2.
 */

// valgrind --log-file="filename" et n hesite pas a aussi mettre --track-fds=yes --trace-children=yes pour le projet on sait jamais 🙂 

// compiler avec les flags pour checker les fd : valgrind --leak-check=full --track-fds=yes --trace-children=yes ./pipex /dev/stdin "cat" "ls" /dev/stdout
int	main(int argc, char **argv, char **envp)
{
	int		end[2];
	t_pipex	*p;
	pid_t	pid;

	p = NULL;
	p = init_pipex(p);
	p->paths = get_paths(envp);
	// La commande ls -la /proc/$$/fd permet de verifier les fd actuellement ouverts.
	// Important : fd has to be closed before beginning the parent process.
	if (argc == 5)
	{
		if (pipe(end) == -1)
		{
			perror("Error pipe\n");
			clean(p->paths);
			free(p);
			close(end[0]);
			close(end[1]);
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid == -1)
		{
			perror("Error pid\n");
			exit(EXIT_FAILURE);
		}
		if (pid == 0) 
		{
			child_process(argv, argv[2], end, p);
		}
		else
		{
			parent_process(argv, argv[3], end, p);
	//		clean(p->paths);
	//		free(p);
	//		waitpid(pid, NULL, 0);
		}
	}
	else
	{
		clean(p->paths);
		free(p);
		exit(EXIT_FAILURE);
	}
	return (0);
}
