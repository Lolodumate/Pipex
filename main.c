/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:09:28 by laroges           #+#    #+#             */
/*   Updated: 2024/01/03 20:31:09 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		end[2];
	t_pipex	*p;
	pid_t	pid;

	p = NULL;
	if (argc == 5)
	{
		p = init_pipex(p);
		p->paths = get_paths(envp);
		check_pipex(p, end);
		pid = fork();
		pipex(argv, end, p, pid);
	}
	return (0);
}
