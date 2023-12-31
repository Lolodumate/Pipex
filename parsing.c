#include "pipex.h"

int	find_path(char **envp, char *to_find)
{
	int		i;

	i = 0;
	if (to_find == NULL || envp == NULL)
		return (-1);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], to_find, 5) == 0)
			return (i);
		i++;
	}
	return (0);
}

// Add a backslash at the end of the string if it's necessary;
char	*add_backslash(char *path)
{
	int		len;

	len = 0;
	if (path == NULL)
		return (NULL);
	len = ft_strlen(path);
	if (path[len - 1] != '/')
		path = ft_strjoin(path, "/");
	return (path);
}

// Check each string to add a blackslash if it's necessary.
char	**check_backslash(char **paths)
{
	int		i;

	i = 0;
	if (paths == NULL)
		return (NULL);
	while (paths[i])
	{
		paths[i] = add_backslash(paths[i]);
		i++;
	}
	return (paths);
}

char	**get_paths(char **envp)
{
	int		i;
	char	*path;
	char	**paths;

	i = find_path(envp, "PATH=");
	if (i == -1)
		return (NULL);
	path = ft_substr(envp[i], 5, ft_strlen(envp[i]) + 1);
	if (path == NULL)
		return (NULL);
	paths = ft_split(path, ':');
	free(path);
	if (paths == NULL)
		return (NULL);
	paths = check_backslash(paths);
	return (paths);
}
