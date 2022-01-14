/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parents.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 12:59:30 by sdonny            #+#    #+#             */
/*   Updated: 2022/01/13 12:59:32 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	rmandopen(char *filename)
{
	if (access(filename, F_OK) == 0)
	{
		if (unlink(filename) == -1)
			return (-1);
	}
	return (open(filename, O_WRONLY | O_CREAT, 0664));
}

int	parentread(char *cmp, int fd, char *filename)
{
	char	*buf;
	int		file;

	file = 0;
	if (!cmp)
		file = open(filename, O_RDONLY);
	if (file == -1)
		return (-1);
	while (1)
	{
		buf = get_next_line(file);
		if (!buf && !cmp)
			break ;
		if (cmp && ft_strncmp(buf, cmp, ft_strlen(cmp)) == 0)
		{
			free(buf);
			break ;
		}
		ft_putstr_fd(buf, fd);
		free(buf);
	}
	close(fd);
	if (!cmp)
		close(file);
	return (0);
}

int	parentwrite(int fd, char *filename, int flag)
{
	char	*buf;
	int		file;

	if (!flag)
		file = rmandopen(filename);
	else
		file = open(filename, O_APPEND | O_CREAT | O_WRONLY, 0664);
	if (file == -1)
		return (-1);
	while (1)
	{
		buf = get_next_line(fd);
		if (!buf)
			break ;
		ft_putstr_fd(buf, file);
		free(buf);
	}
	close(fd);
	close(file);
	return (0);
}

void	waitchildren(pid_t *pid, int **fd, int argc)
{
	int	m;

	m = -1;
	while (++m < argc)
	{
		if (waitpid(pid[m], NULL, 0) == -1)
			exitpid(fd, pid, argc, "waitpid()");
		free(fd[m]);
	}
	free(fd[m]);
	free(fd);
	free(pid);
}
