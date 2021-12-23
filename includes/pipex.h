#ifndef PIPEX_H
#define PIPEX_H
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "../get_next_line.h"
//#include<process.h>
#include<errno.h>
//#include<dos.h>
#include "../libft/libft.h"
typedef struct s_pip
{
	char	*infile;
	char	*outfile;
	char	**comands;
}	t_pip;
#endif
