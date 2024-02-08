/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:15:43 by laroges           #+#    #+#             */
/*   Updated: 2024/02/06 17:11:31 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(char **argv, int *end, t_pipex *p, pid_t pid)
{
	int		status;
	int		i;

	status = 0;
	i = 0;
	if (pid == -1)
	{
		free_str(p->paths);
		ft_error(p, "Error fork");
	}
	if (pid == 0)
		child_process(argv, argv[2], end, p);
	else
		parent_process(argv, argv[3], end, p);
	while (i < 2)
	{
		waitpid(-1, &status, 0);
		i++;
	}
}
