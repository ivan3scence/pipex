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
		perror(pip->infile);
		del_elem(pip);
		strerror(errno);
		exit(1);
	}
	if (access(pip->infile, R_OK))
	{
		perror(pip->infile);
		del_elem(pip);
		strerror(errno);
		exit(1);
	}
}

static void	check_outfile(t_pip *pip)
{
	if (access(pip->outfile, F_OK) != 0)
		return ;
	if (access(pip->outfile, W_OK) != 0)
	{
		perror(pip->outfile);
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
	pip->outfile = argv[argc - 1];
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

static void	change_stdout(t_pip *pip)
{
	int	fd;

	fd = open(pip->outfile, O_WRONLY | O_CREAT, 0777);
	if (fd == -1)
	{
		perror(pip->outfile);
		del_elem(pip);
		strerror(errno);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	change_stdin(t_pip *pip)
{
	int	fd;

	fd = open(pip->infile, O_RDONLY);
	if (fd == -1)
	{
		perror(pip->infile);
		del_elem(pip);
		strerror(errno);
		exit(1);
	}
	dup2(fd, 0);
	close(fd);
}

int	main(int argc, char **argv)
{
	t_pip	*pip;
	char	*ar[2];
	//int	status;
	//int	i;
	pid_t	pid;
	char	*buf;
	char	*buf2="";
	char	*infile[2];

	pip = validate(argc, argv);
	change_stdout(pip);
	change_stdin(pip);
	buf = get_next_line(0);
	while (buf)
	{
		infile[0] = ft_strjoin(buf2, buf);
		free(buf);
		if (*buf2)
			free(buf2);
		buf2 = infile[0];
		buf = get_next_line(1);
	}
	free(buf2);
	infile[1] = NULL;
	ar[0] = "-l\0";
	ar[1] = NULL;
	//status = 0;
	pid = fork();
	argc -= 1;
	if (!pid)
	{
		execve("/bin/wc", ar, NULL);
		exit(0);
	}
	/*else
	{
		wait(&status);
		if (errno)
			strerror(errno);
		printf("%d\n", WIFEXITED(status));
	}*/
	del_elem(pip);
	return (0);
}
