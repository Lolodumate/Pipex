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

// compiler avec les flags pour checker les fd : valgrind --leak-check=full --track-fds=yes --trace-children=yes ./pipex /dev/stdin "cat" "ls" /dev/stdout
int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_pipex	*p;

	p = NULL;
	// La commande ls -la /proc/$$/fd permet de verifier les fd actuellement ouverts.
	// Important : fd has to be closed before beginning the parent process.
//	if (argc >= 2)
	p = init_pipex(p);
	p->paths = get_paths(envp);
	pipex(argv, p);	
	
	clean(p->paths);
	free(p);
	return (0);
}
