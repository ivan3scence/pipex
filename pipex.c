#include "./includes/pipex.h"
#include <stdio.h>

//t_pip	*create_pip(void)
//{
//	t_pip	*elem;
//
//	elem = (t_pip *)malloc(sizeof(t_pip));
//	if (!elem)
//	{
//		perror("not creating pip\n");
//		exit(1);
//	}
//	elem->infile = NULL;
//	elem->outfile = NULL;
//	elem->comands = NULL;
//	return (elem);
//}
//
//void	del_elem(t_pip *pip)
//{
//	if (pip)
//	{
//		free(pip);
//		pip = NULL;
//	}
//}

static void	check_infile(char *infile)
{
	if (access(infile, F_OK) != 0)
	{
		perror(infile);
		strerror(errno);
		exit(1);
	}
	if (access(infile, R_OK) != 0)
	{
		perror(infile);
		strerror(errno);
		exit(1);
	}
}

static void	check_outfile(char *outfile)
{
	if (access(outfile, F_OK) != 0)
		return ;
	if (access(outfile, W_OK) != 0)
	{
		perror(outfile);
		strerror(errno);
		exit(1);
	}
}

//t_pip	*create_elem(int argc, char **argv)
//{
//	t_pip	*pip;
//
//	pip = create_pip();
//	pip->infile = argv[1];
//	pip->outfile = argv[argc - 1];
//	check_infile(pip);
//	check_outfile(pip);
//	pip->comands = &argv[2];
//	argv[argc] = NULL;
//	return (pip);
//}

//t_pip	*validate(int argc, char **argv)
//{
//	t_pip	*pip;
//
//	if (argc < 3)
//	{
//		ft_putstr_fd("too few arguments", 2);
//		exit(1);
//	}
//	pip = create_elem(argc, argv);
//	return (pip);
//}
/*
static void	change_stdout(char *outfile)
{
	int	fd;

	unlink(outfile);
	fd = open(outfile, O_WRONLY | O_CREAT, 0777);
	if (fd == -1)
			exit(1);
	*{
		perror(pip->outfile
						);
		del_elem(pip);
		strerror(errno);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(1);
}

static void	change_stdoutt(int fd)
{

	dup2(fd, STDOUT_FILENO);
	close(STDOUT_FILENO);
}

static void	change_stdin(char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd == -1)
			exit(1);
	{
		perror(infile);
		//del_elem(pip);
		strerror(errno);
		exit(1);
	}
	dup2(fd, 0);
	close(fd);
}


static void	change_stdinn(int fd)
{
	dup2(fd, 0);
	close(0);
}
*/

void    close_fd(int quantity, int proc, int **fd)
{
    int     i;
    int     j;

    i = -1;
    while (++i < quantity)
    {
        j = -1;
        while (++j < 2)
        {
            if (((i == proc && j == 0) || (i == proc + 1 && j == 1))
				|| (((i == quantity - 1 && j == 0) || (i == 0 && j == 1))
					&& proc == -1))
                continue ;
            close(fd[i][j]);
        }
    }
	if ( proc != -1)
	{
		dup2(fd[proc][0], 0);
		close(fd[proc][0]);
		dup2(fd[proc + 1][1], 1);
		close(fd[proc + 1][1]);
	}
}

static void	validate(int argc, char **argv)
{
	check_infile(argv[1]);
	check_outfile(argv[argc - 1]);
}

static void	exitmalloc(int argc, int **fd)
{
	int	i;

	i = -1;
	perror("malloc for pipes\n");
	strerror(errno);
	if (fd)
	{
		while (i < argc - 2)
			free(fd[i]);
		free(fd);
		fd = NULL;
	}
	exit(1);
}

static int	**multipipe(int argc)
{
	int	i;
	int **fd;

	fd = (int **)malloc(sizeof(int *) * (argc - 2));
	if (!fd)
		exitmalloc(argc, NULL);
	i = 0;
	while (i < argc - 2)
	{
		fd[i] = (int *)malloc(sizeof(int) * 2);
		if (!fd[i])
			exitmalloc(argc, NULL);
		if (pipe(fd[i++]) == -1)
		{
			perror("pipe error");
			strerror(errno);
			exit(1);
		}
	}
	return (fd);
}

static void	exitpid(int **fd, pid_t *pid, int argc)
{
	int	i;

	i = -1;
	perror("pid - rip");
	strerror(errno);
	while (++i < argc - 2)
		free(fd[i]);
	free(fd);
	fd = NULL;
	free(pid);
	pid = NULL;
	exit(1);
}

static char	**cmdparse(char *old)
{
	char	**new;
	char	*tmp;

	new = ft_split(old, ' ');
	tmp = new[0];
	new[0] = ft_strjoin("/bin/", tmp);
	free(tmp);
	tmp = NULL;
	ft_putstr_fd(new[0], 1);
	return (new);
}

static void	cleancmd(char **cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
		free(cmd[i]);
	free(cmd);
	cmd = NULL;
}

static void	forks(int **fd, int argc, char	**argv, char **envp)
{
	int		m;
	int		p;
	pid_t	*pid;
	char	**cmd;

	m = -1;
	p = -1;
	pid = (pid_t *)malloc(sizeof(pid_t) * (argc - 3));
	if (!pid)
		exitmalloc(argc, fd);
	while (++m < argc - 3)
	{
		pid[++p] = fork();
		if (pid[p] < 0)
			exitpid(fd, pid, argc);
		if (!pid[p])
		{
			close_fd(argc - 2, m, fd);
			cmd = cmdparse(argv[m + 2]);
			execve(cmd[0], cmd, envp);
			cleancmd(cmd);
			close(0);
			close(1);
			exit(0);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	int     **fd;
	int     m;
	int     pid[argc - 3];

	validate(argc, argv);
	m = -1;
	fd = multipipe(argc);
	forks(fd, argc, argv, envp);
	
	close_fd(argc - 2, -1, fd);
	char *buf;
	int		file;
	file = open("infile", O_RDONLY);
	while (1)
	{
		buf = get_next_line(file);
		//ft_putstr_fd(buf, 1);
		if (!buf)
			break ;
		ft_putstr_fd(buf, fd[0][1]);
		free(buf);
	}
	close(file);
	file = open("outfile", O_WRONLY | O_CREAT, 0664);
	close(fd[0][1]);
	while (1)
	{
		buf = get_next_line(fd[argc - 3][0]);
		if (!buf)
			break ;
		ft_putstr_fd(buf, file);
		free(buf);
	}
	close(file);
	close(fd[argc - 3][0]);
	m = -1;
	while (++m < argc - 3)
		waitpid(pid[m], NULL, 0);
	free(fd);
	exit(0);
}
