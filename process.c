/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 19:57:40 by laroges           #+#    #+#             */
/*   Updated: 2024/01/03 20:02:05 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* For child process :
 * infile has to be the stdin (as input)
 * end[1] has to be the stdout (we write to end[1] the output of cmd1)
 */

void	child_process(char **argv, char *cmd, int *end, t_pipex *p)
{
	int		fd;

	if (!argv || !argv[1])
	{
		exit(EXIT_FAILURE);
	}
	fd = open(argv[1], O_RDONLY, 0644);
	if (fd == -1)
		exit(EXIT_FAILURE);
	dup2(fd, STDIN_FILENO);
	close(end[0]);
	dup2(end[1], STDOUT_FILENO);
	close(end[1]);
	close(end[0]);
	close(fd);
	exec_command(p->paths, cmd, p);
}

/* For parent process :
 * end[0] has to be the stdin (end[0] reads from end[1] the output of cmd1)
 * outfile has to be the stdout(we write to it the output of cmd2)
 */
void	parent_process(char **argv, char *cmd, int *end, t_pipex *p)
{
	int		status;
	int		fd;

	waitpid(-1, &status, 0);
	if (!argv || !argv[4])
		exit(EXIT_FAILURE);
	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit(EXIT_FAILURE);
	dup2(fd, STDOUT_FILENO);
	close(end[1]);
	dup2(end[0], STDIN_FILENO);
	close(end[0]);
	close(end[1]);
	close(fd);
	exec_command(p->paths, cmd, p);
}
