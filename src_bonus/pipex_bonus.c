/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:06:53 by sdonny            #+#    #+#             */
/*   Updated: 2022/01/13 12:02:54 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	cleansplit(char **cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
		free(cmd[i]);
	free(cmd);
	cmd = NULL;
}

char	*checkpath(char *tmp, char **envp)
{
	char	**paths;
	char	*path;
	char	*slesh;
	int		i;

	i = -1;
	while (ft_strnstr(envp[++i], "PATH", 4) == 0)
		;
	paths = ft_split(envp[i] + 5, ':');
	i = -1;
	while (paths[++i])
	{
		slesh = ft_strjoin(paths[i], "/");
		path = ft_strjoin(slesh, tmp);
		free(slesh);
		if (access(path, F_OK) == 0)
		{
			cleansplit(paths);
			return (path);
		}
		free(path);
	}
	cleansplit(paths);
	return (NULL);
}

void	close_fd(int quantity, int proc, int **fd)
{
	int	i;
	int	j;

	i = -1;
	while (++i < quantity)
	{
		j = -1;
		while (++j < 2)
		{
			if ((i == proc && j == 0) || (i == proc + 1 && j == 1)
				|| (((i == quantity - 1 && j == 0) || (i == 0 && j == 1))
					&& proc == -1))
				continue ;
			close(fd[i][j]);
		}
	}
	if (proc != -1)
	{
		dup2(fd[proc][0], 0);
		close(fd[proc][0]);
		dup2(fd[proc + 1][1], 1);
		close(fd[proc + 1][1]);
	}
}

static int	**multipipe(int m)
{
	int	i;
	int	**fd;

	fd = (int **)malloc(sizeof(int *) * m);
	if (!fd)
		exitmalloc(0, fd);
	i = -1;
	while (++i < m)
	{
		fd[i] = (int *)malloc(sizeof(int) * 2);
		if (!fd[i])
			exitmalloc(i, fd);
		if (pipe(fd[i]) == -1)
			exitmalloc(i, fd);
	}
	return (fd);
}

int	main(int argc, char **argv, char **envp)
{
	int		**fd;
	int		m;
	int		check;
	pid_t	*pid;

	if (argc < 4)
	{
		ft_putstr_fd("Error!\nToo few arguments!\n", 2);
		exit(EXIT_FAILURE);
	}
	m = validate(argc, argv);
	fd = multipipe(argc - 2 - m);
	pid = forks(fd, (argc - 3 - m) * (1 - 2 * m), argv, envp);
	close_fd(argc - 2 - m, -1, fd);
	if (!m)
		check = parentread(NULL, fd[0][1], argv[1]);
	else
		check = parentread(argv[2], fd[0][1], NULL);
	if (check == -1)
		exitpid(fd, pid, argc, "parentread");
	check = parentwrite(fd[argc - 3 - m][0], argv[argc - 1], m);
	if (check == -1)
		exitpid(fd, pid, argc, "parentwrite");
	waitchildren(pid, fd, argc - 3 - m);
}
