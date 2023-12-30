#include "pipex.h"

void	exec_command(char **paths, char *argv)
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
		printf("try_path = %s\n", try_path);
		execve(try_path, cmd, NULL);
		free(try_path);
		j++;
	}
	clean(cmd);
	perror("No path");
	exit(EXIT_FAILURE);
}
/*
int	get_size(char *path)
{
	int		size;
	int		i;

	size = 0;
	i = 0;
	while(path[i])
	{
		if (path[i] == ':')
			size++;
		i++;
	}
	return (size);
}

int	get_size_path(char *path, int index)
{
	int		i;

	i = index;
	while (path[i] && path[i] != ':')
		i++;
	return (i - index);
}

char	**path_split(char *path)
{
	int		i;
	int		j;
	int		k;
	int		size;
	char	**paths;

	i = 0;
	j = 0;
	k = 0;
	size = 0;
	if (path == NULL)
		return (NULL);
	paths = malloc(sizeof(char *) * get_size(path) + 1);
	if (paths == NULL)
		return (NULL);
	while (path[i])
	{
		size = get_size_path(path, i);
		paths[j] = malloc(sizeof(char) * size + 1);
		if (paths[j] == NULL)
		{
			free(paths);
			return (NULL);
		}
		while (path[i] && path[i] != ':')
		{
			paths[j][k] = path[i];
			write(1, &path[i], 1);
			i++;
			k++;
		}
		paths[j][k] = '\0';
		size = 0;
		i++;
		j++;
		k = 0;
	}
	return (paths);
}*/
