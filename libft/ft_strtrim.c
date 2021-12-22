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

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	int		i;
	int		j;
	int		n;

	if (!(s1 && set))
		return (0);
	i = -1;
	n = -1;
	j = ft_strlen(s1);
	while (ft_strchr(set, s1[++i]) && s1[i])
		;
	while (ft_strchr(set, s1[--j]) && s1[i])
		;
	trimmed = (char *) malloc(j - i + 2);
	if (!trimmed)
		return (0);
	while (i <= j)
		trimmed[++n] = s1[i++];
	trimmed[++n] = '\0';
	return (trimmed);
}
