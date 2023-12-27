#include "pipex.h"

void	clean(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		printf("Clean str[%d] %s OK\n", i, str[i]);
		i++;
	}
	free(str);
	printf("Clean str OK\n");
}
