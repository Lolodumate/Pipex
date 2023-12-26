#include "pipex.h"

int	check_access_read(char *path)
{
	if (access(path, R_OK) == -1)
	{
		printf("Access READ KO\n");
		return (0);
	}
	else
		printf("Access READ OK\n");
	return (1);
}

int	check_access_write(char *path)
{
	if (access(path, W_OK) == -1)
	{
		printf("Access WRITE KO\n");
		return (0);
	}
	else
		printf("Access WRITE OK\n");
	return (1);
}

int	check_access_delete(char *path)
{
	if (access(path, R_OK) == -1)
	{
		printf("Access DELETE KO\n");
		return (0);
	}
	else
		printf("Access DELETE OK\n");
	return (1);
}
