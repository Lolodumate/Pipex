/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 19:57:40 by laroges           #+#    #+#             */
/*   Updated: 2024/02/06 17:10:34 by laroges          ###   ########.fr       */
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
		ft_error(p, "args");
	fd = open(argv[1], O_RDONLY, 0644);
	if (fd == -1)
		ft_error(p, "fd in");
	if (dup2(fd, STDIN_FILENO) == -1)
		ft_error(p, "in");
	if (dup2(end[1], STDOUT_FILENO) == -1)
		ft_error(p, "in");
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
	int		fd;

	if (!argv || !argv[4])
		ft_error(p, "argv");
	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		ft_error(p, "fd out");
	if (dup2(fd, STDOUT_FILENO) == -1)
		ft_error(p, "dup2");
	if (dup2(end[0], STDIN_FILENO) == -1)
		ft_error(p, "dup2");
	close(end[0]);
	close(end[1]);
	close(fd);
	exec_command(p->paths, cmd, p);
}
