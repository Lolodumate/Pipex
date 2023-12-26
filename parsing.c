#include "pipex.h"

// /usr/bin/echo
/*void	get_path(char **argv)
{
	exec_command("/usr/bin/echo", argv);
}*/
/*
int	main(int argc, char **argv)
{
	(void)argc;
	dup_fd("testfile", "/usr/bin/echo", argv);
*/	//get_path(argv);
/*	return (0);
}*/

int	find_path(char **envp, char *to_find)
{
	int		i;

	i = 0;
	if (to_find == NULL)
		return (-1);
	printf("envp[i] = %s\n", envp[i]);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], to_find, 5) == 0)
		{	
			printf("FIND !! i = %d\n", i);
			return (i);
		}
		printf("envp[%d] = %s\n", i, envp[i]);
		i++;
	}
	printf("NOT FIND !!!\n");
	return (0);
}

// Add a backslash at the end of the string if it's necessary;
char	*add_backslash(char *path)
{
	int		len;

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
	path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
	paths = ft_split(path, ':');
	paths = check_backslash(paths);
	free(path);
	return (paths);
}
