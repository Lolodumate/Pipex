#include "pipex.h"

t_pipex	*init_pipex(t_pipex *p)
{
	p = malloc(sizeof(t_pipex));
	if (p == NULL)
		exit(EXIT_FAILURE);
	p->argv = NULL;
	p->paths = NULL;
	p->here_doc = NULL;
	p->infile = NULL;
	p->infile_cmd = NULL;
	p->outfile_cmd = NULL;
	p->outfile = NULL;
	return (p);
}
