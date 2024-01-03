/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:02:49 by laroges           #+#    #+#             */
/*   Updated: 2024/01/03 20:31:46 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "ft_printf.h"
# include "libft.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	char	**argv;
	char	**paths;
	char	**here_doc;
	char	*infile;
	char	**infile_cmd;
	char	*outfile;
	char	**outfile_cmd;
}	t_pipex;

int			check_argv(char **argv);
int			dup_fd_out(char *file, t_pipex *p, char *cmd);
int			dup_fd_in(char *file, t_pipex *p, char *cmd);
int			find_path(char **envp, char *to_find);
char		*add_backslash(char *path);
char		**check_backslash(char **paths);
char		**get_paths(char **envp);
void		check_pipex(t_pipex *p, int *end);
void		child_process(char **argv, char *cmd, int *end, t_pipex *p);
void		parent_process(char **argv, char *cmd, int *end, t_pipex *p);
void		clean(char **paths);
void		pipex(char **argv, int *end, t_pipex *p, pid_t pid);
void		exec_command(char **paths, char *argv, t_pipex *p);
t_pipex		*init_pipex(t_pipex *p);

#endif
