#include <unistd.h>

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
 *
 *
 *
 */

void	child_process(int f1, int cmd1)
{
	// add protection if dup2() < 0
	// dup2() close stdin, f1 becomes the new stdin
	dup2(f1, STDIN_FILENO); // we want f1 to execve() input
	dup2(end[1], STDOUT_FILENO); // we want end[1] to be execve() stdout
	close(end[0]); // Always close the end of the pipe you don't use !
	close(f1);
	// execve function for each possible path
	exit(EXIT_FAILURE);
}

void	parent_process(int f2, int cmd2)
{
	int		status;

	status = 0;
	waitpid(-1, &status, 0); // To wait for the child to finish his process.
	dup2(f2, ...); // f2 is the stdout.
	dup2(end[0], ...); // end[0] is the stdin.
	close(end[1]);
	close(f2);
	// execve function for each possible path
	exit(EXIT_FAILURE);
}

//-----------------------------------------------------------------------------------------------------
// With the right stdin and stdout, we can execute the command with execve()
int	execve(const char *path, char const **argv, char **envp);
/*	path : the path to our command ("which ls" and "which wc").
 *	argv : the arguments the command needs (for example "ls -la"). Tips : use ft_split to obtain a char **.
 *	envp : the environment variable. Retrieve it in the line named PATH with ft_substr and ft_split and then pass it into execve.
 *
 *
 */


void	pipex(int f1, int f2, char **argv, char **envp)
{
	int		end[2];
	pid_t	parent;

	pipe(end);
	parent = fork(); // fork() splits the process in two sub_processes : returns 0 for child process, 1 for parent process, -1 for error.
	if (parent < 0)
		return (perror("Fork: "));
	if (!parent)
		child_process(f1, cmd1);
	else
		parent_process(f2, cmd2);
}

int	main(int argc, char **argv)
{
	int		f1;
	int		f2;

	// La commande ls -la /proc/$$/fd permet de verifier les fd actuellement ouverts.
	// Important : fd has to be closed before beginning the parent process.
	if (argc >= 4)
	{
		pipex(f1, f2);
	}
	return (0);
}
