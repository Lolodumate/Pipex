/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:18:02 by laroges           #+#    #+#             */
/*   Updated: 2024/01/03 20:30:55 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	clean(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	check_pipex(t_pipex *p, int *end)
{
	if (p->paths == NULL)
	{
		free(p);
		exit(EXIT_FAILURE);
	}
	if (pipe(end) == -1)
	{
		perror("Error pipe\n");
		clean(p->paths);
		free(p);
		close(end[0]);
		close(end[1]);
		exit(EXIT_FAILURE);
	}
}
