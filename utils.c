#include "pipex.h"

int	dup_fd_out(char *file, t_pipex *p, char *cmd)
{
	int		fd;

	fd = open(file, O_WRONLY | O_CREAT, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	exec_command(p->paths, cmd);
	return (0);
}

int	dup_fd_in(char *file, t_pipex *p, char *cmd)
{
	int		fd;

	fd = open(file, O_RDONLY, 0644);
	dup2(fd, STDIN_FILENO);
	close(fd);
	exec_command(p->paths, cmd);
	return (0);
}

int	exec_command(char **paths, char *argv)
{
	int		j;
	char	**cmd;
	char	*try_path;

	j = 0;
	try_path = NULL;
	cmd = ft_split(argv, ' ');
	while (paths[j])
	{
		try_path = ft_strjoin(paths[j], cmd[0]);
		execve(try_path, cmd, NULL);
		free(try_path);
		j++;
	}
	clean(cmd);
//	printf("This line will not be executed.\n");
	return (0);
}

void	ft_pipe(int fd[2], pid_t pid, t_pipex *p, char **argv)
{
	char	buffer[1];

	if (pipe(fd) == -1)
	{
		perror("Error pipe");
		exit(EXIT_FAILURE);
	}
	if (pid == -1)
	{
		perror("Error fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0) // Child process
	{
		if (close(fd[0]) == -1)
		{
			printf("Child process - Erreur close(fd[0])\n");
			exit(EXIT_FAILURE);
		}
//		write(fd[1], "Hello parent!", 13);
		dup_fd_out(argv[1], p, argv[2]);
		if (close(fd[1]) == -1)
		{
			printf("Child process - Erreur close(fd[1])\n");
			exit(EXIT_FAILURE);
		}
		// execve ici ?
		exit(EXIT_SUCCESS);
	}
	else // pid > 0 : Parent process
	{
		if (close(fd[1]) == -1)
		{
			printf("Parent process - Erreur close(fd[1])\n");
			exit(EXIT_FAILURE);
		}
		read(fd[0], buffer, 1);
		dup_fd_in(argv[4], p, argv[3]);
		if (close(fd[0]) == -1)
		{
			printf("Parent process - Erreur close(fd[0])\n");
			exit(EXIT_FAILURE);
		}
		read(fd[0], buffer, 1);
		// execve ici ?
//		printf("Message from child : '%s'\n", buffer);
		exit(EXIT_SUCCESS);
	}
}

// Removes a file from the file system. It returns -1 if an error occurs.
/*
int	unlink_file(char *path_file)
{
	if (unlink(path_file) == 0)
	{
		printf("File successfully deleted.\n");
		return (0);
	}
	else
		printf("Error deleting file.\n");
	return (-1);
}
*/
/*	File descriptors ;
 *	0 stdin
 *	1 stdout
 *	2 stderr
 *	3 infile	open()
 *	4 outfile	open()
 *	5 end[0]
 *	6 end[1]
 */
/*
void	pipex(int f1, int f2, char **argv, char **envp)
{
	int		end[2];
	int		cmd1 = 0;
	int		cmd2 = 0;
	pid_t	parent;

	//f1 = open(argv[1], O_RDONLY);
	//f2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	//if (f1 < 0 || f2 < 0)
	//return ;
	pipe(end);
	parent = fork(); // fork() splits the process in two sub_processes : returns 0 for child process, 1 for parent process, -1 for error.
	if (parent < 0)
		return (perror("Fork: "));
	if (!parent)
		child_process(f1, cmd1);
	else
		parent_process(f2, cmd2);
	printf("%s", envp[1]);
	printf("%s", argv[1]);
}*/
