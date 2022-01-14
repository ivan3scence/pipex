/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 12:59:08 by sdonny            #+#    #+#             */
/*   Updated: 2022/01/13 12:59:09 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	**cmdparse(char *old, char **envp)
{
	char	**new;
	char	*tmp;

	new = ft_split(old, ' ');
	tmp = new[0];
	new[0] = checkpath(tmp, envp);
	free(tmp);
	tmp = NULL;
	return (new);
}

static void	killchild(char **cmd)
{
	cleansplit(cmd);
	close(0);
	close(1);
	exit(EXIT_SUCCESS);
}

static pid_t	*createpids(int quantity, int **fd)
{
	pid_t	*pid;

	pid = (pid_t *)malloc(sizeof(pid_t) * quantity);
	if (!pid)
		exitmalloc(quantity, fd);
	return (pid);
}

static pid_t	*preparefork(int *quantity, int *flag, int **fd)
{
	if (*quantity < 0)
	{
		*flag = 1;
		*quantity = -(*quantity);
	}
	return (createpids(*quantity, fd));
}

pid_t	*forks(int **fd, int quantity, char	**argv, char **envp)
{
	int		m;
	pid_t	*pid;
	char	**cmd;
	int		flag;

	m = -1;
	flag = 0;
	pid = preparefork(&quantity, &flag, fd);
	while (++m < quantity)
	{
		pid[m] = fork();
		if (pid[m] < 0)
			exitpid(fd, pid, quantity, "fork");
		if (!pid[m])
		{
			close_fd(quantity + 1, m, fd);
			cmd = cmdparse(argv[m + 2 + flag], envp);
			if (!cmd[0])
				exitcmd(fd, pid, quantity, argv[m + 2 + flag]);
			if (execve(cmd[0], cmd, envp) == -1)
				exitpid(fd, pid, quantity, cmd[0]);
			killchild(cmd);
		}
	}
	return (pid);
}
