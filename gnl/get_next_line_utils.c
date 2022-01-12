/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:35:01 by sdonny            #+#    #+#             */
/*   Updated: 2021/10/27 15:35:28 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *src)
{
	char	*a;
	int		i;

	i = 0;
	a = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (a == NULL)
		return (a);
	while (src[i])
	{
		a[i] = src[i];
		i++;
	}
	a[i] = '\0';
	return (a);
}
