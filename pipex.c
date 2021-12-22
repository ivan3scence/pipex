#include "./includes/pipex.h"
#include <stdio.h>

t_pip	*create_pip(void)
{
	t_pip	*elem;

	elem = (t_pip *)malloc(sizeof(t_pip));
	if (!elem)
	{
		perror("not creating pip\n");
		exit(1);
	}
	elem->infile = NULL;
	elem->outfile = NULL;
	elem->comands = NULL;
	return (elem);
}

void	del_elem(t_pip *pip)
{
	if (pip)
	{
		free(pip);
		pip = NULL;
	}
}

static void	check_infile(t_pip *pip)
{
	if (access(pip->infile, F_OK))
	{
		del_elem(pip);
		strerror(errno);
		exit(1);
	}
	if (access(pip->infile, R_OK))
	{
		del_elem(pip);
		strerror(errno);
		exit(1);
	}
}

static void	check_outfile(t_pip *pip)
{
	if (access(pip->outfile, F_OK))
	{
		del_elem(pip);
		strerror(errno);
		exit(1);
	}
	if (access(pip->outfile, W_OK))
	{
		del_elem(pip);
		strerror(errno);
		exit(1);
	}
}

t_pip	*create_elem(int argc, char **argv)
{
	t_pip	*pip;

	pip = create_pip();
	pip->infile = argv[1];
	pip->outfile = argv[argc];
	check_infile(pip);
	check_outfile(pip);
	pip->comands = (argv + 2);
	return (pip);
}


t_pip	*validate(int argc, char **argv)
{
	t_pip	*pip;

	if (argc < 3)
	{
		ft_putstr_fd("too few arguments", 2);
		exit(1);
	}
	pip = create_elem(argc, argv);
	return (pip);
}

int	main(int argc, char **argv)
{
	t_pip	*pip;
	//int	status;
	//int	i;
	//pid_t	pid;

	pip = validate(argc, argv);
	
	/*
	status = 0;
	pid = fork();
	argc -= 1;
	if (!pid)
	{
		execve("/bin/grep", argv, NULL);
		exit(0);
	}
	else
	{
		wait(&status);
		if (errno)
			strerror(errno);
		printf("%d\n", WIFEXITED(status));
	}*/
	del_elem(pip);
	return (0);
}
