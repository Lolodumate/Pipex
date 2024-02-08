/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:13:37 by laroges           #+#    #+#             */
/*   Updated: 2024/02/06 16:19:12 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(t_pipex *p, char *msg)
{
	if (p)
	{
		if (p->paths)
			free_str(p->paths);
		free(p);
		p = NULL;
	}
	perror(msg);
	exit(errno);
}

void	ft_dup(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
	{
		perror("Error dup2");
		exit(errno);
	}
}

void	check_pipex(t_pipex *p, int *end)
{
	if (p->paths == NULL)
	{
		free(p);
		exit(errno);
	}
	if (pipe(end) == -1)
	{
		close(end[0]);
		close(end[1]);
		ft_error(p, "Error pipe");
	}
}

void	exec_command(char **paths, char *argv, t_pipex *p)
{
	int		j;
	char	**cmd;
	char	*try_path;

	j = 0;
	try_path = NULL;
	cmd = ft_split(argv, ' ');
	if (access(cmd[0], F_OK) == 0)
		execve(cmd[0], cmd, NULL);
	while (paths[j])
	{
		try_path = ft_strjoin(paths[j], cmd[0]);
		if (access(try_path, F_OK) == 0)
			execve(try_path, cmd, NULL);
		free(try_path);
		j++;
	}
	free_str(cmd);
	ft_error(p, "command not found");
}
