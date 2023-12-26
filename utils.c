#include "pipex.h"
/*
int	dup_fd(char *file, char *path, char **argv)
{
	int		fd;

	fd = open(file, O_WRONLY | O_CREAT, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	exec_command(path, argv);
	return (0);
}*/

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
		try_path = ft_strjoin(paths[j], argv);
//		printf("path[%d] = %s\n", j, paths[j]);
//		printf("argv[2] = %s\n", argv);
		printf("try_path = %s\n", try_path);
		execve(try_path, cmd, NULL);
		free(try_path);
		j++;
	}
	j = 0;
	while(cmd[j])
	{
		free(cmd[j]);
		j++;
	}
	free(cmd);
	printf("This line will not be executed.\n");
	return (0);
}

void	ft_pipe(int fd[2], pid_t pid)
{
	char	buffer[13];

	if (pipe(fd) == -1)
	{
		perror("Error pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Error fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		close(fd[0]);
		write(fd[1], "Hello parent!", 13);
		close(fd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(fd[1]);
		read(fd[0], buffer, 13);
		close(fd[0]);
		printf("Message from child : '%s'\n", buffer);
		exit(EXIT_SUCCESS);
	}
}

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

/*	File descriptors ;
 *	0 stdin
 *	1 stdout
 *	2 stderr
 *	3 infile	open()
 *	4 outfile	open()
 *	5 end[0]
 *	6 end[1]
 */
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
}
