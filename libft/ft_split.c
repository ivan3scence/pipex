/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 12:37:50 by sdonny            #+#    #+#             */
/*   Updated: 2021/10/11 15:18:46 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_cleanarr(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
	return (0);
}

static int	ft_strs(const char *s, char c)
{
	int	i;
	int	d;
	int	count;

	count = 0;
	d = 0;
	i = 0;
	if (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] != c && (!s[i + 1] || s[i + 1] == c))
			count++;
		else if (s[i] != c)
			d = 1;
		i++;
	}
	if (!count && d)
		count++;
	return (count);
}

static int	ft_strtoar(const char *s, int j, char **array, int num)
{
	int	n;

	n = -1;
	array[num] = (char *) malloc(sizeof(char) * (j + 1));
	if (!array[num])
	{
		ft_cleanarr(array);
		return (0);
	}
	while (j--)
	{
		array[num][++n] = *s;
		s++;
	}
	array[num][++n] = '\0';
	return (1);
}

static char	**ft_array(char **array, int strs, const char *s, char c)
{
	int	i;
	int	num;
	int	j;

	i = -1;
	j = 0;
	num = 0;
	while (s[++i])
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (!s[i])
			break ;
		j = 0;
		while (s[i + j] != c && s[i + j] != '\0')
			j++;
		if (!ft_strtoar(&s[i], j, array, num++))
			return (0);
		if (s[i + j] == '\0')
			break ;
		i = i + j;
	}
	array[strs] = 0;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		strs;

	strs = 1;
	if (!s)
		return (0);
	if (!ft_strlen(s))
		strs = 0;
	if (strs)
		strs = ft_strs(s, c);
	array = (char **) malloc(sizeof(char *) * (strs + 1));
	if (!array)
		return (0);
	if (strs == 0)
	{
		array[0] = 0;
		return (array);
	}
	return (ft_array(array, strs, s, c));
}
