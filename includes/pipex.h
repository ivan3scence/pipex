/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 13:22:44 by sdonny            #+#    #+#             */
/*   Updated: 2022/01/13 13:22:46 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include "get_next_line.h"
# include "../libft/libft.h"

typedef struct s_pip
{
	char	*infile;
	char	*outfile;
	char	**comands;
}	t_pip;
void	cleansplit(char **cmd);
char	*checkpath(char *tmp, char **envp);
void	close_fd(int quantity, int proc, int **fd);
pid_t	*forks(int **fd, int quantity, char	**argv, char **envp);
int		parentread(char *cmp, int fd, char *filename);
int		parentwrite(int fd, char *filename, int flag);
void	waitchildren(pid_t *pid, int **fd, int argc);
int		validate(int argc, char **argv);
void	exitmalloc(int quantity, int **fd);
void	exitpid(int **fd, pid_t *pid, int quantity, char *desc);
void	exitcmd(int **fd, pid_t *pid, int quantity, char *cmd);
#endif
