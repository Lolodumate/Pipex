#include "pipex.h"

void	exec_command(char **paths, char *argv, t_pipex *p)
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
	clean(p->paths);
	free(p);
	perror("command not found");
	exit(EXIT_FAILURE);
}
