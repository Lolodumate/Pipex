/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:23:17 by laroges           #+#    #+#             */
/*   Updated: 2024/01/03 20:24:12 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipex	*init_pipex(t_pipex *p)
{
	p = malloc(sizeof(t_pipex));
	if (p == NULL)
		exit(errno);
	p->argv = NULL;
	p->paths = NULL;
	p->here_doc = NULL;
	p->infile = NULL;
	p->infile_cmd = NULL;
	p->outfile_cmd = NULL;
	p->outfile = NULL;
	return (p);
}
